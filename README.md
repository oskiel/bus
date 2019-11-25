# Echtzeitanzeige für Kieler Busse

In diesem Tutorial wird beschrieben, wie man eine Echtzeitanzeige für die Busse in Kiel baut.

## Vorraussetzung:
Die Arduino IDE: https://www.arduino.cc/en/main/software
Ein Micro USB Kabel, wie man es für die meisten Android-Handys hat.
[Ein Wemos D1 mini Board](https://www.amazon.de/Ferrell-D1-Mini-ESP8266-NodeMcu/dp/B00A3PHBB8/ref=asc_df_B00A3PHBB8/?tag=googshopde-21&linkCode=df0&hvadid=309904068239&hvpos=1o1&hvnetw=g&hvrand=5184402880504239967&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9060698&hvtargid=pla-562155174651&psc=1&th=1&psc=1&tag=&ref=&adgrpid=67371909331&hvpone=&hvptwo=&hvadid=309904068239&hvpos=1o1&hvnetw=g&hvrand=5184402880504239967&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9060698&hvtargid=pla-562155174651)
[Ein LCD Display 16x4 Zeichen](https://www.amazon.de/SunFounder-Interface-Backlight-Raspberry-MEGA2560/dp/B07MZ2JQ5V/ref=pd_sbs_147_t_1/258-3447105-5599544?_encoding=UTF8&pd_rd_i=B07MZ2JQ5V&pd_rd_r=cb467a2c-a391-4997-8977-37b359cd7347&pd_rd_w=L30VE&pd_rd_wg=PN0za&pf_rd_p=a2f6bca6-dcb1-4822-8e28-66b64b37970e&pf_rd_r=229BJ95GYK8PBXCZHBRA&psc=1&refRID=229BJ95GYK8PBXCZHBRA)
Ein paar Kabel, eventuell Lötzinn und Lötkolben, falls man es verlöten möchte. Zum Testen kann man es auch erstmal mit Kabel stecken.

## Verkabeln
Verkabelt den Wemos D1 mini mit dem LCD Screen wie auf diesem Bild: https://i2.wp.com/www.esp8266learning.com/wp-content/uploads/2017/12/wemos-and-i2c-lcd_bb.png?w=1347

## Software aufspielen
1.) Verbinde den Wemos D1 per USB-Kabel mit dem Computer.

2.) Öffnet die Arduino IDE

3.) In der Arduino IDE Einstellungen öffnen -> unter "Zusätzliche Boardverwalter-URLs" "http://arduino.esp8266.com/stable/package_esp8266com_index.json" einfügen.

4.) Unter "Werkzeuge" -> "Board" -> "Wemos D1 R1" auswählen.

5.) Unter "Werkzeuge" -> "Port" den Port auswählen, in dem usb vorkommt.

6.) Alles aus der Datei bus.c in diesem Repository kopieren und den Code in den Sketch einfügen.

7.) Pakete installieren, im Zweifel Google nutzen, um die fehlenden Pakete zu finden
