import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';

import { get, parseInt } from 'lodash';
import { Observable, forkJoin, iif, of } from 'rxjs';
import { map, flatMap } from 'rxjs/operators';

import { SectionTopic } from '../../dstore/services/section';
import { SectionService } from '../../services/section.service';
import { BaseService } from '../../dstore/services/base.service';
import { AppService } from '../../services/app.service';

import { App } from '../../dstore/services/app';
import { SortOrder } from '../app-title/app-title.component';

@Component({
  selector: 'app-topic',
  templateUrl: './topic.component.html',
  styleUrls: ['./topic.component.scss'],
})
export class TopicComponent implements OnInit {
  constructor(
    private route: ActivatedRoute,
    private appService: AppService,
    private sectionService: SectionService,
  ) {}

  server = BaseService.serverHosts.operationServer;
  topic$: Observable<SectionTopic>;
  apps$: Observable<App[]>;

  ngOnInit() {
    this.topic$ = this.route.paramMap.pipe(
      flatMap(param => {
        const sectionIndex = parseInt(param.get('section'), 10);
        const topicIndex = parseInt(param.get('topic'), 10);
        return this.sectionService
          .getList()
          .map(sectionList => get(sectionList, [sectionIndex, 'items', topicIndex]));
      }),
    );
    this.apps$ = this.topic$.pipe(
      flatMap(topic => {
        const appNameList = topic.apps.filter(app => app.show).map(app => app.name);
        return iif(
          () => appNameList.length === 0,
          of([]),
          forkJoin(appNameList.map(appName => this.appService.getApp(appName))),
        );
      }),
    );
  }
}