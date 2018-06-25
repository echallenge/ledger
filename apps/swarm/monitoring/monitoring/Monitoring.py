import os
import requests
import re
import sys
import time
import threading
import json

class Monitoring(object):

    class WorkerThread(threading.Thread):
        def __init__(self, owner):
            self.done = False
            self.owner = owner
            self.port = 0
            super().__init__(group=None, target=None, name="pollingthread")

        def run(self):
            while not self.done:
                self.poll(self.port + 10000, self.port)
                self.port = (self.port + 1) % 180
                if self.port == 0:
                    time.sleep(2)                    

        def poll(self, port, nodenumber):
            ident = "127.0.0.1:{}".format(nodenumber + 9000)
            try:
                url = "http://127.0.0.1:{}/peers".format(port)
                data = None
                try:
                    r = requests.get(url)
                    if r.status_code == 200:
                        data = json.loads(r.content.decode("utf-8", "strict"))
                        print(url, r.content)
                        peers = data.get("peers", [])
                        state = data.get("state", 0)
                except requests.exceptions.ConnectionError as ex:
                    data = None
                
                if data != None:
                   self.owner.newData(ident, peers, state)
                else:
                    self.owner.badNode(ident)
                
            except Exception as x:
                print("ERR:", x)
            
                
    def __init__(self):
        self.thread = Monitoring.WorkerThread(self)
        self.thread.start()

        self.world = {}

    def close(self):
        self.thread.done = True
        self.thread.join(100)

    def newData(self, ident, peers, state):
        self.world.setdefault(ident, {})
        self.world[ident].setdefault("peers", [])
        self.world[ident].setdefault("state", 0)

        
        self.world[ident]["state"] = state
        self.world[ident]["peers"] = peers

    def badNode(self, ident):
        self.world.pop(ident, None)

