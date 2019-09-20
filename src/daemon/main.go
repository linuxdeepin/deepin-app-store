package main

import (
	"flag"
	"os"
	"path/filepath"
	"time"

	"pkg.deepin.io/lib/dbusutil"
	"pkg.deepin.io/lib/log"
)

var logger = log.NewLogger("deepin-app-store-daemon")

const (
	dbusServiceName = "com.deepin.AppStore.Daemon"
	dbusBackendPath = "/com/deepin/AppStore/Backend"
)

var cacheFolder string
var configFolder string
var iconFolder string

func init() {
	if os.Getenv("XDG_CACHE_HOME") != "" {
		cacheFolder = os.Getenv("XDG_CACHE_HOME")
	} else {
		cacheFolder = filepath.Join(os.Getenv("HOME"), ".cache")
	}
	cacheFolder += "/deepin/deepin-app-store-daemon"
	os.MkdirAll(cacheFolder, 0755)

	iconFolder = cacheFolder + "/icons"
	os.MkdirAll(iconFolder, 0755)

	if os.Getenv("XDG_CONFIG_HOME") != "" {
		configFolder = os.Getenv("XDG_CONFIG_HOME")
	} else {
		configFolder = filepath.Join(os.Getenv("HOME"), ".config")
	}
	configFolder += "/deepin/deepin-app-store"
	os.MkdirAll(configFolder, 0755)
}

func main() {
	daemon := flag.Bool("daemon", false, "run as daemon and not exist")

	flag.Parse()

	service, err := dbusutil.NewSessionService()
	if err != nil {
		logger.Fatal(err)
	}

	block := newBlocklist()

	b, err := newBackend(service)
	if err != nil {
		logger.Fatal(err)
	}
	b.init()
	b.block = block

	err = service.Export(dbusBackendPath, b)
	if err != nil {
		logger.Fatal(err)
	}

	s := NewSettings()
	err = service.Export(dbusSettingsPath, s)
	if err != nil {
		logger.Fatal(err)
	}

	m := NewMetadata()

	m.debBackend = b
	b.metadata = m
	m.settings = s
	m.block = block

	err = service.Export(dbusMetadataPath, m)

	// caller := service.Conn().Object("com.deepin.pusher", "/com/deepin/pusher")
	// err = caller.Call("com.deepin.pusher.Register", 0, "store", dbusServiceName, dbusMetadataPath, dbusMetadataInterface).Store()
	// if nil != err {
	// 	logger.Errorf("register message handler failed: %v", err)
	// }

	err = service.RequestName(dbusServiceName)
	if err != nil {
		logger.Fatal(err)
	}

	logger.Infof("start deepin-app-store-daemon")
	service.SetAutoQuitHandler(3*time.Minute, func() bool {
		if *daemon {
			return false
		}

		b.PropsMu.Lock()
		jobCount := len(b.jobs)
		b.PropsMu.Unlock()
		return jobCount == 0
	})

	service.Wait()
}
