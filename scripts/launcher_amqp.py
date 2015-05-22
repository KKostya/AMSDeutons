import os
import sys
import glob
import pika as p

def pflush(str):
    print str
    sys.stdout.flush()

srcPath = "/afs/cern.ch/user/k/kostams/eos/ams/MC/AMS02/2014/protons.B1034/pr.pl1.1200.qgsp_bic_ams/"
dstPath = "/data/protonsB1034"

connection = p.BlockingConnection(p.ConnectionParameters(host='localhost'))
channel = connection.channel()
channel.queue_declare(queue='task_queue', durable=True)

def getn(f):
    return f.split('/')[-1].replace('.root','').replace('.ntuple','') 

for f in glob.glob(os.path.join(srcPath,"*.root")):  
    inf = getn(f)
    command = "../ntupleData {1}/{0}.root -o {2}/{0}.ntuple.root".format(inf,srcPath,dstPath)

    channel.basic_publish(exchange='',
                          routing_key='task_queue',
                          body=command,
                          properties=pika.BasicProperties(
                             delivery_mode = 2, # make message persistent
                          ))

    pflush(" [x] Sent " + command)

connection.close()
