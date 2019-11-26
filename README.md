# Echtzeitanzeige für Kieler Busse

In diesem Tutorial wird beschrieben, wie man eine Echtzeitanzeige für die Busse in Kiel baut.

## Vorraussetzung:
Die Arduino IDE: https://www.arduino.cc/en/main/software

Ein Micro USB Kabel, wie man es für die meisten Android-Handys hat.

[Ein Wemos D1 mini Board](https://www.amazon.de/Ferrell-D1-Mini-ESP8266-NodeMcu/dp/B00A3PHBB8/ref=asc_df_B00A3PHBB8/?tag=googshopde-21&linkCode=df0&hvadid=309904068239&hvpos=1o1&hvnetw=g&hvrand=5184402880504239967&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9060698&hvtargid=pla-562155174651&psc=1&th=1&psc=1&tag=&ref=&adgrpid=67371909331&hvpone=&hvptwo=&hvadid=309904068239&hvpos=1o1&hvnetw=g&hvrand=5184402880504239967&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9060698&hvtargid=pla-562155174651)

[Ein LCD Display 20x4 Zeichen mit I2C Adapter](https://www.amazon.de/SunFounder-Interface-Backlight-Raspberry-MEGA2560/dp/B07MZ2JQ5V/ref=pd_sbs_147_t_1/258-3447105-5599544?_encoding=UTF8&pd_rd_i=B07MZ2JQ5V&pd_rd_r=cb467a2c-a391-4997-8977-37b359cd7347&pd_rd_w=L30VE&pd_rd_wg=PN0za&pf_rd_p=a2f6bca6-dcb1-4822-8e28-66b64b37970e&pf_rd_r=229BJ95GYK8PBXCZHBRA&psc=1&refRID=229BJ95GYK8PBXCZHBRA) (der Adapter ist meist schon angelötet, das ist perfekt, sonst muss man damit noch rumfummeln, gibt es auch günstiger bei China-Seiten wie Aliexpress, dauert dann aber ne halbe Ewigkeit, bis das Paket da ist.)

Ein paar Kabel, eventuell Lötzinn und Lötkolben, falls man es verlöten möchte. Zum Testen kann man es auch erstmal mit Kabel stecken.

## Verkabeln
Verkabelt den Wemos D1 mini mit dem LCD Screen wie auf diesem Bild: https://i2.wp.com/www.esp8266learning.com/wp-content/uploads/2017/12/wemos-and-i2c-lcd_bb.png?w=1347

## Software aufspielen
1.) Verbinde den Wemos D1 per USB-Kabel mit dem Computer.

2.) Öffnet die Arduino IDE

3.) In der Arduino IDE Einstellungen öffnen -> unter "Zusätzliche Boardverwalter-URLs" "http://arduino.esp8266.com/stable/package_esp8266com_index.json" einfügen.

4.) Unter "Werkzeuge" -> "Board" -> "Wemos D1 R1" auswählen.

5.) Unter "Werkzeuge" -> "Port" den Port auswählen, in dem usb vorkommt.

6.) Alles aus der Datei bus/bus.ino in diesem Repository kopieren und den Code in den Sketch einfügen.

7.) Pakete installieren, im Zweifel Google nutzen, um die fehlenden Pakete zu finden

8.) Eigenes WIFI-Passwort und WIFI-Name im Code ergänzen

9.) https://www.kvg-kiel.de/fahrplan/echtzeit/ hier die eigene Haltestellen herausfinden. Wenn man die Haltestelle sucht und auswählt, sieht man oben in der Adressleiste https://www.kvg-kiel.de/fahrplan/echtzeit/#?stop=1062&language=de die Nummer der Haltestelle (1062 in diesem Beispiel). Die kopieren und im Code einfügen. Es können zwei Haltestellen ausgewählt werden und in die Felder eingetragen werden.

10.) Per "Überprüfen" und "Hochladen" kompilieren und auf den angeschlossenen Arduino hochladen.

## Anmerkung
Ich bin nicht gerade ein C++ Experte, nutze sonst eigentlich vor allem Python, deswegen kann es gut sein, dass das Ganze deutlich effizienter machbar ist. Wenn jemand Ideen hat, um den Code zu verbessern, nehme ich gerne Pull-Requests an. Ich habe übrigens festgestellt, dass es manchmal zu Problemen kommt, wenn sehr viele Busse an einer Haltestelle fahren. Ich denke, dass das irgendein Speicher-Problem ist, konnte aber noch nicht herausfinden, wie man das behebt. 
