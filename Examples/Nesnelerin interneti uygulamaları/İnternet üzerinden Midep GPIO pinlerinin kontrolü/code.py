import time
import digitalio # import Adafruit Blinka
import board
# import Adafruit IO REST client.
from Adafruit_IO import Client, Feed, RequestError

# Adafruit IO key'i yazin.
ADAFRUIT_IO_KEY = '...'

# Adafruit IO username'i yazin.
ADAFRUIT_IO_USERNAME = 'YOUR_AIO_USERNAME'

# REST istemcisinin bir örnegini olusturun.
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

try: # 'digital' adında bir feed varsa
    digital = aio.feeds('digital')
except RequestError: # yoksa 'digital' adında feed olustur.
    feed = Feed(name="digital")
    digital = aio.create_feed(feed)

# led set up
led = digitalio.DigitalInOut(board.D5)
led.direction = digitalio.Direction.OUTPUT

while True:
    data = aio.receive(digital.key)
    if int(data.value) == 1:
        print('received <- ON\n')
    elif int(data.value) == 0:
        print('received <- OFF\n')

    # LED'i feed degerine ayarla
    led.value = int(data.value)
    time.sleep(0.5)
