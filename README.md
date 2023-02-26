# c-student-registration-system
student registration system
# projenin amacı
C dilinde dosyalama fonksiyonlarının pratiğinin yapılmasıdır. Bu amaçla ikili dosyaların (binary file) ve metin dosyalarının (text file) kullanıldığı bir uygulama geliştirilecektir.
# projenin tanımı
Projede bizden istenen, C dilini kullanarak yoğun indeks yapısı kullanılarak dosyalama fonksiyonları pratiğinin yapılmasıdır.Bu indeks yapısında ikili dosya olarak gerçekleştirilen veri dosyasındaki her kayıt için indeks dosyasında bir girdi saklanmaktadır.İndeks dosyasında kayıtlar adres anahtar şeklinde saklanmaktadır.Adres değeri anahtar ile ilgili bilginin veri dosyasında hangi ofsette saklandığını göstermektir.Bizden istenilen öncelikle 50 kişilik öğrencinin öğrenci numarasını,puanını,ders kodunu ve adresininin
txt ve binary dosyalara kaydedilmesi ve daha sonra girilen veriler doğrultusunda verilerin hangi offsetde saklandığının text dosyasına kaydedilmesidir.Text dosyasında offsetler haricinde bir diğer önemli nokta ise girilen verilerin öğrenci numaraların sıaralı bir biçimde text dosyasında gözükmesidir.Bu işlemler için
bizden belirli fonksiyonlar kullanmamız istenmektedir.Kullanılması istenen  fonksiyonlar şunlardır:
indexDosyasiOlustur,kayitEkle,kayitBul,kayitSil,kayitGuncelle,veriDosyasiniGoster,indeksDosyasiniGoster,indeksDosyasiniSil.
Kullanılması istenen bir yapı daha bulunmaktadır.
  struct kayit
{int ogrNo;
int dersKodu;
int puan;
}
Bize verilen bu bilgiler doğrultusunda çalışmalarımızı yürüttük.Projenin yapım süreci boyunca karşılaştığımız zorluklardan ve bizdeki eksikliklerden aşağıda bahsettik
# arastırmalar ve yöntem
Projenin eksiksiz bir biçimde çalışması için öncelikle proje ile bağlantılı bütün dosyaların klasörde bulunması gerekmektedir.Kullanıcı kodu derlediğinde önüne menü gelmektedir.Yapmak istediği işleme bu menü üzerinden karar verir.
![image](https://user-images.githubusercontent.com/73225797/221406746-87e64f4c-d157-46f9-a480-086af0841e66.png)
Menü çalıştıktan sonra öğrencinin seçeneğine göre işlemler uygulanır.Öğrenci eğer 1’i seçerse karşısına şöyle bir ekran çıkıcaktır.
![image](https://user-images.githubusercontent.com/73225797/221406773-9d8f5ff6-d289-4501-9c27-64de63195973.png)
Kayıt ekleme yapacağı zaman gireceği öğrenciye ait  sırasıyla öğrenci numarası,ders kodu ve puan bilgilerini girer.Kullanıcının girdiği bilgiler  öncelikle binary dosyaya kaydedilir.

Kullanıcı eğer 2 numaralı seçeneği seçerse
içinde offset değerlerimizi tutacak olan indeks dosyamız oluşacaktır.

Kullanıcı 3 numaralı seçeneği seçerse indeks 
Dosyasına kaydedilen değerleri görecektir.
Kullanıcı 4 numaralı seçeneği seçerse oluşturulan indeks dosyası silinecektir.

Kullanıcı 5 numaralı seçeneği seçerse öğrenci numarası yardımıyla aranan kayıtı bulacaktır.Bu kısım için Binary Search algoritması kullanılmıştır.

Kullanıcı 6 numaralı seçeneği seçerse 
girilen öğrenci numarasına ait olan kayıt güncellenecektir ve yalnızca puan bilgisi değiştirelecektir.

Kullanıcı 7 numaralı seçeneği seçerse
kullanıcının istediği kayıt silinecektir.

Kullanıcı 8 numaralı seçeneği seçerse
veri dosyasındaki kayıtlar sıralanmamış biçimde gösterilecektir.
#Fonksiyon İsimleri ve Açıklamalrı
1.IndexDosyasiOlustur Fonksiyonu
50 kayıtlık sırasız veri dosyası için indeks dosyası oluşturulur.

2.kayıtEkle Fonksiyonu
Veri dosyasına yeni bir kayıt ekleme işlemi bu fonksiyonla gerçekleştirilir. Yeni kayıt her zaman fonksiyonun sonuna eklenir ve işlemlerin sonunda indeks dosyası da güncellenir.

3.kayitBul Fonksiyonu
Öğrenci numarasına göre arama işlemi yapılır. Bir öğrenci numarası için birden fazla ders kodu ve puan olabileceği için aranılan kayıt bulunana kadar öğrenci numarasına ait tüm kayıtların listelenmesi gerekir. Bu işlemde binary search algoritması kullanılacaktır.

4.kayitSil Fonksiyonu
KayitBul fonksiyonunda bulunan kayıt silinecektir. Silme işlemi indeks dosyasına da yansıtılacaktır.

5.kayitGuncelle Fonksiyonu
Öğrenci numarasıyla yapılan arama sonucunda bulunan kaydın sadece puan alanı güncellenecektir.

6.VeriDosyasiniGoster Fonksiyonu
Yapılacak işlemlerin üzerinde gerçekleştirileceği veri dosyası listelenecektir.

7.IndeksDosyasınıGoster Fonksiyonu
Kayıtlı sıralı halinin bulunacağı indeks dosyası listelenecektir.Selection Sort algoritması kullanılmıştır.

8.IndeksDosyasiniSil Fonksiyonu
İndeks dosyasını diskten silecektir.

#istatistikler
Program kodumuz yaklaşık 450 satır tek dosyadan oluşmaktadır. Okuyucunun anlamasını kolaylaştırmak için bazı yorum satırlarına yer verilmiştir.
#Programın Derlenmesi
Projeyi CodeBlocks ya da herhangi bir derleyici  kullanarak derleyebilirsiniz.Derledikten sonra herhangi bir girdi girdiğinizdeki  text ve binary 
dosyasındaki değişimlere veriDosyasi.bin uzantılı binary ve  indexDosyasi.txt uzantılı dosyalardan istediğiniz zaman erişim sağlayabileceksiniz.
#Geliştirme Ortamı
Projemizi Windows sistemde,Codeblocks üzerinde geliştirip GCC kullanarak derledik.
#Akış Diyagramı
![image](https://user-images.githubusercontent.com/73225797/221406937-cb50a140-9e8b-4370-912a-97a1dd78eb02.png)
