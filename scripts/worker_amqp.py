import os
import sys
import pika as p
 
def pflush(str):
    print str
    sys.stdout.flush()


def callback(ch, method, properties, body):

    pflush( " [x]  Executing " + body )

    pflush( " [x] Job done ..." )
    ch.basic_ack(delivery_tag = method.delivery_tag)


connection = p.BlockingConnection(p.ConnectionParameters(host='localhost'))
channel = connection.channel()

channel.queue_declare(queue='task_queue', durable=True)
pflush(' [*] Waiting for messages. To exit press CTRL+C')

channel.basic_qos(prefetch_count=1)
channel.basic_consume(callback, queue='task_queue')
channel.start_consuming()
