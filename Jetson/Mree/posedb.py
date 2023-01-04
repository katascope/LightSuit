#!/usr/bin/python3

class PoseDB:
    def print(self):
        for key in self.db:
            print(str(key) + " = " + str(self.db[key]));

    def read(self):
        self.f = open(self.filename,"r")
        for line in self.f:
            line = line.rstrip('\n').rstrip('\r')
            name = str(line).split(" ")[0];
            self.db[name] = str(line)
        PoseDB.print(self)

    def __init__(self,fn):
        self.db = { };
        self.filename = str(fn)
        PoseDB.read(self)

    def write(self,line):
        print("Writing " + str(line))
        name = str(line).split(" ")[0];
        self.db[name] = str(line)
        self.f = open(self.filename,"w")
        for key in self.db:
            print(str(key) + " = " + str(self.db[key]));
            self.f.write( str(self.db[key]) + "\n");
        self.f.close()

