#include <stdio.h>
#include <locale.h>
#include <malloc.h>

struct kayit{
    int ogrNO;
    int dersKodu;
    int puan;


};
FILE *indexDosyasi;
FILE *veriDosyasi;

void indexDosyasiOlustur();
void kayitEkle();
void kayitBul();
void kayitSil();
void kayitGuncelle();
void veriDosyasiniGoster();
void indexDosyasiniGoster();
void indexDosyasiniSil();
void kayitEk();
int indexDosyaKayitSayisi();
int main() {
    setlocale(LC_ALL,"turkish");
    //kayitEk();
    while(1){

        printf("\nKayit Ekle (1)\nIndex Dosyasi Olustur (2)\nIndex Dosyasini Goster (3)\nIndex Dosyasini Sil (4)\nKayit Bul (5)\nKayit Guncelle (6)\nKayit Sil(7)\nVeri Dosyasini Goster (8)\n");
        int input;
        printf(">>");
        scanf("%d",&input);
        printf("\n");
        if(input==1){kayitEkle();}
        else if(input==2){indexDosyasiOlustur();}
        else if(input==3){indexDosyasiniGoster();}
        else if(input==4){indexDosyasiniSil();}
        else if(input==5){kayitBul();}
        else if(input==6){kayitGuncelle();}
        else if(input==7){kayitSil();}
        else if(input==8){veriDosyasiniGoster();}
        else{
            break;
        }
        fflush(stdin);
        getchar();


    }

    return 0;
}
void indexDosyasiOlustur(){
    // ilk diziye at>> binary s?rala>> index dosyas?na yazd?r
//    int records[100][2];//[index]-[0:ogrno][1:offset]
    int recordcount=0;
    if ((veriDosyasi = fopen("veridosyasi.bin","ab+")) == NULL){
        printf("dosya hatasi!");
        return;
    }

    struct kayit temp;
    fseek(veriDosyasi,0L,SEEK_END);
    int size= ftell(veriDosyasi);
    int kayitsayisi=size/ sizeof(struct kayit);
    rewind(veriDosyasi);
    //int (*records)[kayitsayisi] = malloc(sizeof(double[kayitsayisi][2]));
    int records[100][2];
    for(int offset = 0; offset < kayitsayisi; offset++)
    {
        fread(&temp, sizeof(struct kayit), 1, veriDosyasi);
        if(temp.ogrNO!=-1){
            records[recordcount][0]=temp.ogrNO;
            records[recordcount][1]=offset* sizeof(struct kayit);
            recordcount++;
        }
    }
    fclose(veriDosyasi);
    //siralama ba?lang??
    int min_index;
    int tmp1,tmp2;
    for (int i = 0; i < recordcount-1 ; ++i) {
        min_index=i;
        for (int j = i+1; j < recordcount ; ++j) {
            if(records[j][0]<records[min_index][0])
                min_index=j;
        }
        tmp1=records[min_index][0], tmp2=records[min_index][1];
        records[min_index][0]=records[i][0];
        records[min_index][1]=records[i][1];
        records[i][0]=tmp1;
        records[i][1]=tmp2;
    }




    //s?ralama son
    indexDosyasi = fopen("indexDosyasi.txt","w");
    if(indexDosyasi==NULL){ printf("dosya hatasi!");return;}
    for (int i = 0; i < recordcount; ++i) {
        fprintf(indexDosyasi,"%d %d\n",records[i][0],records[i][1]);
        // ogrNO bo?luk offset ?eklinde index dosyasina yazd?r?r.
    }
    printf("\nIndex dosyasi olusturuldu.");
    fclose(indexDosyasi);
    //free(records);
    return;
}
void kayitEkle(){
    if ((veriDosyasi = fopen("veridosyasi.bin","ab+")) == NULL){
        printf("dosya hatasi!");
        return;
    }

    struct kayit temp;
    printf("ogrenci no:");
    scanf("%d",&temp.ogrNO);
    printf("ders kodu:");
    scanf("%d",&temp.dersKodu);
    printf("puan:");
    scanf("%d",&temp.puan);
    fwrite(&temp,sizeof(struct kayit),1,veriDosyasi );
    fclose(veriDosyasi);
    printf("\nKayit Eklendi");
    indexDosyasiOlustur();
    return;
}
void kayitEk(){
    if ((veriDosyasi = fopen("veridosyasi.bin","ab+")) == NULL){
        printf("dosya hatasi!");
        return;
    }

    for(int i=1;i<11;i++){

        struct kayit temp;
        printf("ogrenci no:");
        temp.ogrNO=i;
        printf("ders kodu:");
        temp.dersKodu=5;
        printf("puan:");
        temp.puan=i*10;
        fwrite(&temp,sizeof(struct kayit),1,veriDosyasi );

        printf("\nKayit Eklendi");
    }
    fclose(veriDosyasi);
    indexDosyasiOlustur();
    return;
}

void kayitGoster(int offset){
    if ((veriDosyasi = fopen("veridosyasi.bin","ab+")) == NULL){
        printf("dosya hatasi");
        return;}
    struct kayit temp;

    fseek(veriDosyasi,offset,SEEK_SET);//istenilen offsete git
    fread(&temp, sizeof(struct kayit), 1, veriDosyasi);
    printf("\nKayit Bilgileri> ogrNO:%d dersKodu:%d puan:%d\n",temp.ogrNO,temp.dersKodu,temp.puan);
    fclose(veriDosyasi);
    return;
}

void kayitBul(){
    int x;
    int recordCount=0;
    int ogrNO,offset;
    char c;
    int count;
    if ((indexDosyasi = fopen("indexDosyasi.txt","r")) == NULL){printf("dosya hatasi!");}
    for (c = getc(indexDosyasi); c != EOF; c = getc(indexDosyasi))
        if (c == '\n')
            count = count + 1;


    fclose(indexDosyasi);

    printf("Anahtar(ogrNO):");
    scanf("%d",&x);
    int records[100][2];//[index]-[0:ogrNO][1:offset]
    //int (*records)[count] = malloc(sizeof(double[count][2]));

    if ((indexDosyasi = fopen("indexDosyasi.txt","r")) == NULL){printf("dosya hatasi!");return;}

    while (fscanf(indexDosyasi,"%d %d",&ogrNO,&offset)!=-1){
        records[recordCount][0]=ogrNO;
        records[recordCount][1]=offset;
        recordCount++;
    }
    fclose(indexDosyasi);
    //binary search ba?la
    int left,right,middle;
    left=0;right=recordCount;
    int bulundu=0;

    while(left<=right){
        middle=(left+(right-1))/2;
        if(records[middle][0]==x){
            bulundu=1;
            printf("Kayit Bulundu");
            kayitGoster(records[middle][1]);
            //sola bak
            int m=middle-1;
            while(records[m][0]==x){
                printf("Kayit Bulundu");
                kayitGoster(records[m][1]);
                m--;
            }
            //sa?a bak
            m=middle+1;
            while(records[m][0]==x){
                printf("Kayit Bulundu");
                kayitGoster(records[m][1]);
                m++;
            }
            break;
        }
        if(records[middle][0]<x){
            left=middle+1;
        }
        else{
            right=middle-1;
        }
    }
    //binary search son
    if(bulundu==0){
        printf("Kayit Bulunamadi");
    }
    //free(records);
}
void sil(int offset){
    int c;
    printf("\nBu Kaydi Sil Evet:1 Hayir:0  :");
    scanf("%d",&c);
    if(c==1){


        if ((veriDosyasi = fopen("veridosyasi.bin","rb+")) == NULL){
            printf("dosyas hatasi");
            return;}
        struct kayit temp;
        temp.ogrNO=-1;temp.dersKodu=-1;temp.puan=-1;
        fseek(veriDosyasi,offset,SEEK_SET);//istenilen offsete git
        fwrite(&temp, sizeof(struct kayit),1,veriDosyasi);
        printf("\nKayit Silindi");
        fclose(veriDosyasi);
        indexDosyasiOlustur();

    }
    else{
        return;
    }
}
void kayitSil(){
    int x;
    int recordCount=0;
    int ogrNO,offset;
    printf("Anahtar(ogrNO):");
    scanf("%d",&x);
    int records[100][2];//[index]-[0:ogrNO][1:offset]
    if ((indexDosyasi = fopen("indexDosyasi.txt","r")) == NULL){printf("Error!");return;}
    while (fscanf(indexDosyasi,"%d %d",&ogrNO,&offset)!=-1){
        records[recordCount][0]=ogrNO;
        records[recordCount][1]=offset;
        recordCount++;
    }
    fclose(indexDosyasi);
    //binary search ba?la
    int left,right,middle;
    left=0;right=recordCount;
    int bulundu=0;

    while(left<=right){
        middle=(left+(right-1))/2;
        if(records[middle][0]==x){
            bulundu=1;
            printf("Kayit Bulundu\n");
            kayitGoster(records[middle][1]);
            sil(records[middle][1]);
            //sola bak
            int m=middle-1;
            while(records[m][0]==x){
                printf("Kayit Bulundu\n");
                kayitGoster(records[m][1]);
                sil(records[m][1]);
                m--;
            }
            //sa?a bak
            m=middle+1;
            while(records[m][0]==x){
                printf("Kayit Bulundu\n");
                kayitGoster(records[m][1]);
                sil(records[m][1]);
                m++;
            }
            break;
        }
        if(records[middle][0]<x){
            left=middle+1;
        }
        else{
            right=middle-1;
        }
    }
    //binary search son
    if(bulundu==0){
        printf("Kayit Bulunamadi");
    }
}
void guncelle(int offset){
    int c;
    printf("\nBu kaydi guncelle Evet:1 Hay?r:0  :");
    scanf("%d",&c);
    if(c==1){
        int yenipuan;
        printf("\nYeni puan degeri giriniz:");
        scanf("%d",&yenipuan);
        if ((veriDosyasi = fopen("veridosyasi.bin","rb+")) == NULL){
            printf("dosya hatasi");
            return;}
        struct kayit temp_old;
        fseek(veriDosyasi,offset,SEEK_SET);//istenilen offsete git
        fread(&temp_old, sizeof(struct kayit), 1, veriDosyasi);

        temp_old.puan=yenipuan;
        fseek(veriDosyasi,offset,SEEK_SET);//istenilen offsete git

        fwrite(&temp_old, sizeof(struct kayit),1,veriDosyasi);
        printf("\nKayit Guncellendi\n");

        fclose(veriDosyasi);
        indexDosyasiOlustur();

    }
    else{
        return;
    }
}
void kayitGuncelle(){
    int x;
    int recordCount=0;
    int ogrNO,offset;
    printf("Anahtar(ogrNO):");
    scanf("%d",&x);
    int records[100][2];//[index]-[0:ogrNO][1:offset]
    if ((indexDosyasi = fopen("indexDosyasi.txt","r")) == NULL){printf("hata!");return;}
    while (fscanf(indexDosyasi,"%d %d",&ogrNO,&offset)!=-1){
        records[recordCount][0]=ogrNO;
        records[recordCount][1]=offset;
        recordCount++;
    }
    fclose(indexDosyasi);
    //binary search ba?la
    int left,right,middle;
    left=0;right=recordCount;
    int bulundu=0;

    while(left<=right){
        middle=(left+(right-1))/2;
        if(records[middle][0]==x){
            bulundu=1;
            printf("Kayit Bulundu\n");
            kayitGoster(records[middle][1]);
            guncelle(records[middle][1]);
            //sola bak
            int m=middle-1;
            while(records[m][0]==x){
                printf("Kayit Bulundu\n");
                kayitGoster(records[m][1]);
                guncelle(records[m][1]);
                m--;
            }
            //sa?a bak
            m=middle+1;
            while(records[m][0]==x){
                printf("Kayit Bulundu\n");
                kayitGoster(records[m][1]);
                guncelle(records[m][1]);
                m++;
            }
            break;
        }
        if(records[middle][0]<x){
            left=middle+1;
        }
        else{
            right=middle-1;
        }
    }
    //binary search son
    if(bulundu==0){
        printf("Kayit Bulunamad?");
    }


}
void veriDosyasiniGoster(){
    if ((veriDosyasi = fopen("veridosyasi.bin","ab+")) == NULL){
        printf("dosya hatasi");
        return;
    }

    struct kayit temp;
    fseek(veriDosyasi,0L,SEEK_END);
    int size= ftell(veriDosyasi);
    int kayitsayisi=size/ sizeof(struct kayit);
    rewind(veriDosyasi);
    int count=1;
    for(int n = 0; n < kayitsayisi; n++)
    {
        fread(&temp, sizeof(struct kayit), 1, veriDosyasi);
        if(temp.ogrNO!=-1){
            printf("%d.Kayit: ogrNO: %d\tdersKodu: %d\tpuan: %d\n",count, temp.ogrNO,temp.dersKodu,temp.puan);
            count++;
        }
    }
    fclose(veriDosyasi);
    return;
}
void indexDosyasiniGoster(){
    int ogrNO,offset;
    if ((indexDosyasi = fopen("indexDosyasi.txt","r")) == NULL){printf("Error!");return;}
    while (fscanf(indexDosyasi,"%d %d",&ogrNO,&offset)!=-1){
        printf("ogrNO: %d offset: %d\n",ogrNO,offset);
    }
    fclose(indexDosyasi);
}
void indexDosyasiniSil(){
    int delete;
    delete= remove("indexDosyasi.txt");
    if(!delete){
        printf("\nIndex dosyasi silindi.");
    }
    else{
        printf("\nIndex dosyasi silinemedi");
    }
}
