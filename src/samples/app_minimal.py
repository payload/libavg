#!/usr/bin/env python
# -*- coding: utf-8 -*-

from libavg import app

class MyMainDiv(app.MainDiv):
    def onInit(self):
        self.toggleTouchVisualization()

    def onExit(self):
        pass

    def onFrame(self):
        pass

app.App().run(MyMainDiv())

