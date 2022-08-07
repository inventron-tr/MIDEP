import serial
import time
import schedule
import smtplib
 
def main_func():
    arduino = serial.Serial(port='/dev/ttymxc2', baudrate=9600)
    print('Arduino ile seri iletisim basladi')
    arduino_data = arduino.readline()
    decoded_value = str(arduino_data[0:len(arduino_data)].decode("utf-8"))
    
    if decoded_value[0] == '1':
        print(decoded_value[0])
        
        sent_from = gmail_user
        to = ['...@gmail.com']
        subject = 'Su baskini alarmi'
        body = 'Dikkat!! Evinizde su baskini tehlikesi algilandi. Lutfen kontrol ediniz.'
        
        email_text = """\
        From: %s
        To: %s
        Subject: %s
        %s
        
        """ % (sent_from, ", ".join(to), subject, body)
        try:
            smtp_server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
            smtp_server.ehlo()
            smtp_server.login(gmail_user, gmail_password)
            smtp_server.sendmail(sent_from, to, email_text)
            smtp_server.close()
            print ("Email basari ile gonderildi!")
        except Exception as ex:
            print ("Email gonderiminde hata….",ex)

    arduino_data = 0
    arduino.close()
    print('baglanti sonlandi')
    print('<------------------------------------->')
 
gmail_user = '...@gmail.com'
gmail_password = '…'
 
print ('program basladi')
 
schedule.every(20).seconds.do(main_func)
 
while True:
    schedule.run_pending()
    time.sleep(1)
