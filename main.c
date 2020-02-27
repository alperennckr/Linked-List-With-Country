#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node;
typedef struct node1 node1;
struct node1
{
    int plaka;
    node1 *next1;
};
struct node
{
    char isim[20];
    int plaka;
    char bolge[5];
    int komsusayisi;
    node *next;
    node *prev;
    node *komsu;
};
struct node *ilk=NULL;
struct node *ilk1=NULL;
struct node *son=NULL;
void komsuekle(struct node *liste,int plaka)
{
    if(liste->komsu==NULL)
    {
        struct node1 *temp=(struct node1*)malloc(sizeof(struct node1));
        temp->plaka=plaka;
        temp->next1=NULL;
        liste->komsu=temp;
        return 0;
    }
    struct node1 *temp1=liste->komsu;
    while(temp1->next1!=NULL)
        temp1=temp1->next1;
    struct node1 *temp2=(struct node1*)malloc(sizeof(struct node1));
    temp2->plaka=plaka;
    temp2->next1=temp1->next1;
    temp1->next1=temp2;
    return 0;

}
void komsusirala(struct node *liste)
{
    struct node1 *komsular,*adim;
    int temp;
    while(liste!=NULL)
    {
        adim=liste->komsu;
        while(adim->next1!=NULL)
        {
            komsular=liste->komsu;
            while(komsular->next1!=NULL)
            {

                if(komsular->plaka>komsular->next1->plaka)
                {
                    temp=komsular->plaka;
                    komsular->plaka=komsular->next1->plaka;
                    komsular->next1->plaka=temp;

                }
                komsular=komsular->next1;
            }
            adim=adim->next1;
        }

        liste=liste->next;

    }
}
void yaz(struct node *liste,FILE *dosya2)
{
    struct node1 *komsular;
    while(liste!=NULL)
    {
        printf("%d %s %s ",liste->plaka,liste->isim,liste->bolge);
        fprintf(dosya2,"%d %s %s ",liste->plaka,liste->isim,liste->bolge);
        komsular=liste->komsu;
        while(komsular!=NULL)
        {
            printf("%d ",komsular->plaka);
            fprintf(dosya2,"%d ",komsular->plaka);
            komsular=komsular->next1;
        }
        printf("\n");
        fputs("\n",dosya2);
        liste=liste->next;
    }

}
int komsumu(struct node1 *komsular,int plaka)
{
    while(komsular!=NULL)
    {
        if(komsular->plaka==plaka)
        {
            return 1;
        }
        komsular=komsular->next1;
    }
    return 0;

}
int kontrol(struct node *liste,char isim[],int plaka,char bolge[])
{
    struct node *temp=liste;
    while(temp!=NULL)
    {
        if(strcmp(temp->isim,isim)==0)
        {
            printf("Girdiginiz sehirle ayni isimde sehir bulunmaktadir.\n");
            return 0;
        }
        temp=temp->next;
    }
    temp=liste;
    while(temp!=NULL)
    {
        if(plaka==temp->plaka)
        {
            printf("Girdiginiz sehirle ayni plakada sehir bulunmaktadir.\n");
            return 0;
        }
        temp=temp->next;
    }
    return 1;

}
int main()
{
    char bilgi[100];
    char *ch;
    int sayac=0,say=0,says=0,sayk=0;
    FILE *dosya=fopen("sehirler.txt","r");
    FILE *dosya2=fopen("cikti.txt","w");
    while(fgets(bilgi,"%s",dosya)!=NULL)
    {
        struct node *yeni=(struct node*)malloc(sizeof(struct node));
        ch=strtok(bilgi,",");
        while(ch!=NULL)
        {
            if(sayac==0){ yeni->plaka=atoi(ch); says++;}
            if(sayac==1) strcpy(yeni->isim,ch);
            if(sayac==2) strcpy(yeni->bolge,ch);
            ch=strtok(NULL,",");
            sayac++;
        }
        if(ilk==NULL)
        {
            ilk=yeni;
            son=yeni;
            son->next=NULL;
            son->prev=ilk;
        }
        else
        {
             if(yeni->plaka<ilk->plaka)
                {
                    yeni->prev=NULL;
                    yeni->next=ilk;
                    ilk=yeni;
                }
            else{
                    if(yeni->plaka>son->plaka){
                        son->next=yeni;
                        yeni->prev=son;
                        ilk->prev=yeni;
                        son=yeni;
                        yeni->next=NULL;
                }
                else if(yeni->plaka<son->plaka){
                    yeni->prev=son->prev;
                    son->prev->next=yeni;
                    yeni->next=son;
                    son->next=NULL;
                    son->prev=yeni;
                }
                struct node *temp=ilk;
                    while(temp->next!=NULL){
                         if(yeni->plaka<temp->plaka){
                            sayk=1; break;
                         }
                      temp=temp->next;
                    }

                 if(sayk==1){
                 yeni->prev->next=yeni->next;
                 yeni->next->prev=yeni->prev;
                  yeni->prev=temp->prev;
                  temp->prev->next=yeni;
                  yeni->next=temp;
                  temp->prev=yeni;
                  }
           }
        }
        sayac=0;
        sayk=0;
    }
    struct node *liste=ilk;
    struct node *liste1=ilk;
     liste=ilk;
    while(liste!=NULL)
    {
        liste->komsu=NULL;
        liste=liste->next;
    }
    liste=ilk;
    int komsusay=0,sayb=0;
    char sehir[20];
    fclose(dosya);
    dosya=fopen("sehirler.txt","r");
    struct node *temp=ilk;
    int tut;
    while(fgets(bilgi,"%s",dosya)!=NULL)
    {
        ch=strtok(bilgi,",\n");
        while(ch!=NULL)
        {
            if(sayac==1){
                tut=atoi(bilgi);
                while(temp!=NULL){
                    if(temp->plaka==tut){
                        break;
                    }
                    temp=temp->next;
                }
            }
            if(sayac>2)
            {
                strcpy(sehir,ch);
                struct node *liste=ilk;
                while(liste!=NULL)
                {
                    if(strcmp(sehir,liste->isim)==0)
                    {
                        komsuekle(temp,liste->plaka);
                    }
                    liste=liste->next;
                }

            }
            ch=strtok(NULL,",\n");
            sayac++;
        }
        sayac=0;
        temp=ilk;
    }
    liste=ilk;
    while(liste!=NULL)
    {
        say++;

        liste=liste->next;
    }
    liste=ilk;
    komsusirala(liste);
    liste=ilk;
    struct node1 *komsular;
    while(liste!=NULL)
    {
        fprintf(dosya2,"%d %s %s",liste->plaka,liste->isim,liste->bolge);

        komsular=liste->komsu;
        while(komsular!=NULL)
        {
            fprintf(dosya2,"->%d",komsular->plaka);
            komsular=komsular->next1;

        }
        sayb++;

        fputs("\n",dosya2);
        if(sayb!=say)
        fputs("||",dosya2);
        fputs("\n",dosya2);
        liste=liste->next;
    }
    fclose(dosya2);
    int secim,plaka,buldu=0,sayac1=0;
    char isim[50],bolge[5];
    char ara[20],eklenecek[20];
    liste=ilk;
    struct node1 *komsulara;
    while(liste!=NULL)
    {
        komsulara=liste->komsu;
        while(komsulara!=NULL)
        {
            komsusay++;
            komsulara=komsulara->next1;
        }
        liste->komsusayisi=komsusay;
        liste=liste->next;
        komsusay=0;
    }
    int buldu1=0;
    dosya2=fopen("cikti.txt","a");
    while(1)
    {
        printf("Yeni sehir eklemek icin 1'e basiniz.\nKomsu eklemek icin 2'ye basiniz.\nArama yapmak icin 3'e basiniz.\nSehir silmek icin 4'e\n");
        fputs("Yeni sehir eklemek icin 1'e basiniz.\nKomsu eklemek icin 2'ye basiniz.\nArama yapmak icin 3'e basiniz.\nSehir silmek icin 4'e\n",dosya2);
        printf("Komsu silmek icin 5'e\nBolgedeki sehirleri yazdirmak icin 6'ya basiniz.\nBelirli komsu kriterine gore siniflandirmak icin 7'ye\n");
        fputs("Komsu silmek icin 5'e\nBolgedeki sehirleri yazdirmak icin 6'ya basiniz.\nBelirli komsu kriterine gore siniflandirmak icin 7'ye\n",dosya2);
        printf("Belli bir sayi araliginda komsu sayisina sahip sehirlerden ortak komsulara sahip olan sehirlerin listelemek icin 8'e\n");
        fputs("Belli bir sayi araliginda komsu sayisina sahip sehirlerden ortak komsulara sahip olan sehirlerin listelemek icin 8'e\n",dosya2);
               printf("Sehirler listesini yazdirmak icin 9'a\nCikmak icin 10'a basiniz.");
        scanf("%d",&secim);
        fputs("Sehirler listesini yazdirmak icin 9'a\nCikmak icin 10'a basiniz.",dosya2);
        fputs("\n\n",dosya2);
        fprintf(dosya2,"seciminiz: %d\n",secim);
        switch(secim)
        {

        case 1:
            printf("Ekleyeceginiz sehirin ismini,plakasini ve iki harf seklinde bolgesini giriniz:");
            scanf("%s%d%s",&isim,&plaka,&bolge);
            fputs("Ekleyeceginiz sehirin ismini,plakasini ve iki harf seklinde bolgesini giriniz:\n",dosya2);
            fprintf(dosya2,"Seciminiz: %s %d %s\n",isim,plaka,bolge);
            fputs("\n\n",dosya2);
            liste=ilk;
            if(kontrol(liste,isim,plaka,bolge)==1)
            {
                struct node *ekle=(struct node*)malloc(sizeof(struct node));
                struct node *temp=liste;
                struct node *temp2=liste;
                ekle->plaka=plaka;
                strcpy(ekle->isim,isim);
                strcpy(ekle->bolge,bolge);
                ekle->next=NULL;
                ekle->prev=NULL;
                if(plaka<liste->plaka)
                {
                    liste->prev=NULL;
                    ekle->next=liste;
                    liste=ekle;
                    ilk=liste;
                    break;
                }
                while(temp2->next!=NULL)
                {
                    temp2=temp2->next;
                }
                if(temp2->plaka<plaka)
                {
                    ekle->prev=temp2;
                    temp2->next=ekle;
                    ekle->next=NULL;
                    break;
                }
                temp=liste;
                while(temp->next!=NULL && temp->next->plaka<plaka)
                {
                    temp=temp->next;
                }
                temp2=temp;
                ekle->prev=temp;
                ekle->next=temp->next;
                temp->next=ekle;
                break;
            }
            break;

        case 2:
            buldu=0;
            printf("Hangi sehire komsu ekleyeceksiniz ?");
            scanf("%s",&eklenecek);
            fputs("Hangi sehire komsu ekleyeceksiniz ?\n",dosya2);
            fprintf(dosya2,"Komsu eklemek istediginiz sehir: %s\n",eklenecek);
            liste=ilk;
            while(liste!=NULL)
            {
                if(strcmp(liste->isim,eklenecek)==0)
                {
                    buldu=1;
                    printf("Ekleyeceginiz komsu sehrin plaka kodunu giriniz:");
                    scanf("%d",&plaka);
                    fputs("Ekleyeceginiz komsu sehrin plaka kodunu giriniz:\n",dosya2);
                    fprintf(dosya2,"Girdiginiz plaka kodu:%d \n",plaka);
                    fputs("\n\n",dosya2);
                    if(komsumu(liste->komsu,plaka)==0)
                    {
                        buldu1=1;
                        liste->komsusayisi+=1;
                        komsuekle(liste,plaka);
                        komsular=liste->komsu;
                        komsulara=liste->komsu;
                        while(komsulara->next1!=NULL)
                        {
                            komsular=liste->komsu;
                            while(komsular->next1!=NULL)
                            {
                                if(komsular->plaka>komsular->next1->plaka)
                                {
                                    int temp=komsular->plaka;
                                    komsular->plaka=komsular->next1->plaka;
                                    komsular->next1->plaka=temp;
                                }
                                komsular=komsular->next1;
                            }
                            komsulara=komsulara->next1;
                        }
                    }
                    else if(komsumu(liste->komsu,plaka)==1){
                    printf("Girdiginiz plaka zaten sectiginiz sehrin komsusu\n");
                    fputs("Girdiginiz plaka zaten sectiginiz sehrin komsusu\n\n",dosya2);
                    break;}
                }
                liste=liste->next;
            }
            if(buldu==0)
            {
                printf("Girdiginiz sehir bulunmamaktadir.\n");
                fputs("Girdiginiz sehir bulunmamaktadir.\n\n",dosya2);
            }
            if(buldu1==0)
            {
                printf("Girdiginiz plaka bulunmamaktadir.\n");
                fputs("Girdiginiz plaka bulunmamaktadir.\n\n",dosya2);
            }
            break;
        case 3:
            printf("Bilgisini arayacaginiz sehrin ismi veya plakasini giriniz:");
            scanf("%s",&ara);
            fputs("Bilgisini arayacaginiz sehrin ismi veya plakasini giriniz:\n",dosya2);
            fprintf(dosya2,"%s\n",ara);
            if(isdigit(ara[0]))
            {
                plaka=atoi(ara);
                liste=ilk;
                while(liste!=NULL)
                {
                    if(liste->plaka==plaka)
                    {
                        buldu=1;
                        printf("Sehrin adi: %s\n",liste->isim);
                        fprintf(dosya2,"Sehrin adi: %s\n",liste->isim);
                        printf("Sehrin plakasi: %d\n",liste->plaka);
                        fprintf(dosya2,"Sehrin plakasi: %d\n",liste->plaka);
                        printf("Sehrin bolgesi: %s\n",liste->bolge);
                        fprintf(dosya2,"Sehrin bolgesi: %s\n",liste->bolge);
                        printf("Sehrin komsu sayisi: %d\n",liste->komsusayisi);
                        fprintf(dosya2,"Sehrin komsu sayisi: %d\n",liste->komsusayisi);
                        printf("Sehrin komsulari:\n");
                        fputs("Sehrin komsulari:\n",dosya2);
                        komsular=liste->komsu;
                        while(komsular!=NULL)
                        {
                            liste1=ilk;
                            while(liste1!=NULL)
                            {
                                if(liste1->plaka==komsular->plaka)
                                {
                                    sayac1++;
                                    printf("%d)Komsu sehrin adi:%s\n",sayac1,liste1->isim);
                                    fprintf(dosya2,"%d)Komsu sehrin adi:%s\n",sayac1,liste1->isim);
                                    printf("Komsu sehrin plaka:%d\n",liste1->plaka);
                                    fprintf(dosya2,"Komsu sehrin plaka:%d\n",liste1->plaka);
                                    printf("Komsu sehrin bolgesi:%s\n",liste1->bolge);
                                    fprintf(dosya2,"Komsu sehrin bolgesi:%s\n",liste1->bolge);
                                }
                                liste1=liste1->next;
                            }
                            komsular=komsular->next1;
                            liste1=ilk;
                        }
                        sayac1=0;
                    }
                    liste=liste->next;
                }
            }
            else if(isalpha(ara[0]))
            {
                liste=ilk;
                while(liste!=NULL)
                {
                    if(strcmp(liste->isim,ara)==0)
                    {
                        buldu=1;
                        printf("Sehrin adi: %s\n",liste->isim);
                        fprintf(dosya2,"Sehrin adi: %s\n",liste->isim);
                        printf("Sehrin plakasi: %d\n",liste->plaka);
                        fprintf(dosya2,"Sehrin plakasi: %d\n",liste->plaka);
                        printf("Sehrin bolgesi: %s\n",liste->bolge);
                        fprintf(dosya2,"Sehrin bolgesi: %s\n",liste->bolge);
                        printf("Sehrin komsu sayisi: %d\n",liste->komsusayisi);
                        fprintf(dosya2,"Sehrin komsu sayisi: %d\n",liste->komsusayisi);
                        printf("Sehrin komsulari:\n");
                        fputs("Sehrin komsulari:\n",dosya2);
                        komsular=liste->komsu;
                        while(komsular!=NULL)
                        {
                            liste1=ilk;
                            while(liste1!=NULL)
                            {
                                if(liste1->plaka==komsular->plaka)
                                {
                                    sayac1++;
                                    printf("%d)Komsu sehrin adi:%s\n",sayac1,liste1->isim);
                                    fprintf(dosya2,"%d)Komsu sehrin adi:%s\n",sayac1,liste1->isim);
                                    printf("Komsu sehrin plaka:%d\n",liste1->plaka);
                                    fprintf(dosya2,"Komsu sehrin plaka:%d\n",liste1->plaka);
                                    printf("Komsu sehrin bolgesi:%s\n",liste1->bolge);
                                    fprintf(dosya2,"Komsu sehrin bolgesi:%s\n",liste1->bolge);
                                }
                                liste1=liste1->next;
                            }
                            komsular=komsular->next1;
                            liste1=ilk;
                        }
                        sayac1=0;
                    }
                    liste=liste->next;
                }
            }
            if(buldu==0)
            {
                char ch[2];
                printf("Sehir listede yok.Eklemek ister misiniz? E/H");
                scanf("%s",&ch);
                fputs("Sehir listede yok.Eklemek ister misiniz? E/H",dosya2);
                fprintf(dosya2,"Seciminiz: %s",ch);
                if(strcmp(ch,"H")==0)
                {
                    break;
                }
                else if(strcmp(ch,"E")==0)
                {

                    liste=ilk;
                    struct node *ekle=(struct node*)malloc(sizeof(struct node));
                    struct node *temp=liste;
                    struct node *temp2=liste;
                    if(isdigit(ara[0]))
                    {
                        plaka=atoi(ara);
                        printf("Ekleyeceginiz sehrin isim ve bolgesini giriniz:");
                        scanf("%s%s",&isim,&bolge);
                        fputs("Ekleyeceginiz sehrin isim ve bolgesini giriniz:\n",dosya2);
                        fprintf(dosya2,"Seciminiz:%s %s\n",isim,bolge);
                        ekle->plaka=plaka;
                        strcpy(ekle->isim,isim);
                        strcpy(ekle->bolge,bolge);
                        if(plaka<liste->plaka)
                        {
                            ekle->next=liste;
                            liste=ekle;
                            ilk=liste;
                            break;
                        }
                        while(temp2->next!=NULL)
                        {
                            temp2=temp2->next;
                        }
                        if(temp2->plaka<plaka)
                        {
                            temp2->next=ekle;
                            temp2=ekle;
                            ekle->next=NULL;
                            break;
                        }
                        temp=liste;
                        while(temp->next!=NULL && temp->next->plaka<plaka)
                        {
                            temp=temp->next;
                        }
                        temp2=temp;
                        ekle->next=temp->next;
                        temp->next=ekle;
                        break;
                    }
                    else if(isalpha(ara[0]))
                    {
                        liste=ilk;
                        printf("Ekleyeceginiz sehrin plaka ve bolgesini giriniz:");
                        scanf("%d%s",&plaka,&bolge);
                        fputs("Ekleyeceginiz sehrin plaka ve bolgesini giriniz:\n",dosya2);
                        fprintf("Seciminiz: %d %s\n",plaka,bolge);
                        ekle->plaka=plaka;
                        strcpy(ekle->isim,ara);
                        strcpy(ekle->bolge,bolge);
                        if(plaka<liste->plaka)
                        {
                            ekle->next=liste;
                            liste=ekle;
                            ilk=liste;
                            break;
                        }
                        while(temp2->next!=NULL)
                        {
                            temp2=temp2->next;
                        }
                        if(temp2->plaka<plaka)
                        {
                            temp2->next=ekle;
                            temp2=ekle;
                            ekle->next=NULL;
                            break;
                        }
                        temp=liste;
                        while(temp->next!=NULL && temp->next->plaka<plaka)
                        {
                            temp=temp->next;
                        }
                        temp2=temp;
                        ekle->next=temp->next;
                        temp->next=ekle;
                        break;

                    }
                }
            }
            break;
        case 4:
            printf("Silmek istediginiz sehirin ismini giriniz.");
            scanf("%s",&sehir);
            fputs("Silmek istediginiz sehirin ismini giriniz.\n",dosya2);
            fprintf(dosya2,"Seciminiz: %s\n",sehir);
            liste=ilk;
            int sildi=0;
            if(strcmp(liste->isim,sehir)==0)
            {
                sildi=1;
                liste=liste->next;
                ilk=liste;
                break;
            }
            struct node *temp=liste;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            if(strcmp(temp->isim,sehir)==0)
            {
                sildi=1;
                temp->prev->next=NULL;
                break;
            }
            liste=ilk;
            struct node *temp1=liste;
            while (temp1->next != NULL)
            {
                if (strcmp(temp1->isim,sehir)==0)
                {
                    sildi=1;
                    break;
                }
                temp1 = temp1->next;
            }
            if(sildi==1)
            {
                temp1->prev->next=temp1->next;
                temp1->next->prev=temp1->prev;
                break;
            }
            if(sildi==0)
            {
                printf("Girdiginiz sehir bulunmamaktadir.\n");
                fputs("Girdiginiz sehir bulunmamaktadir.\n",dosya2);
            }
            break;
        case 5:
            printf("Hangi sehirin komsuluklarindan birini silmek istiyorsunuz ?");
            scanf("%s",&sehir);
            fputs("Hangi sehirin komsuluklarindan birini silmek istiyorsunuz ?",dosya2);
            fprintf(dosya2,"Seciminiz: %s\n",sehir);
            liste=ilk;
            sildi=0;
            while(liste!=NULL)
            {
                if(strcmp(liste->isim,sehir)==0)
                {
                    printf("%s sehrinin hangi komsusunu sileceksiniz,plaka olarak giriniz.",sehir);
                    scanf("%d",&plaka);
                    fprintf(dosya2,"%s sehrinin hangi komsusunu sileceksiniz,plaka olarak giriniz.\n",sehir);
                    fprintf(dosya2,"Seciminiz: %d\n",plaka);
                    struct node1 *komsular,*temp;
                    int girdi=0;
                    komsular=liste->komsu;
                    if(komsular->plaka==plaka)
                    {
                        sildi=1;
                        liste->komsu=komsular->next1;
                        break;
                    }
                    temp=liste->komsu;
                    while(temp->next1->next1!=NULL)
                    {
                        temp=temp->next1;
                    }
                    if(temp->next1->plaka==plaka)
                    {
                        sildi=1;
                        temp->next1=NULL;
                        break;
                    }
                    struct node1 *temp2=liste->komsu;
                    while(temp2->next1!=NULL)
                    {
                        if(temp2->next1->plaka==plaka)
                        {
                            sildi=1;
                            girdi=1;
                            break;
                        }
                        temp2=temp2->next1;
                    }
                    if(girdi==1)
                    {
                        struct node1 *temp3 = temp2->next1->next1;
                        struct node1 *temp4 = temp2;
                        free(temp2->next1);
                        temp4->next1 = temp3;
                    }

                }
                liste=liste->next;
            }
            if(sildi==0)
                printf("Girdiginiz plaka bu sehrin bir komsusu degildir.");
            fputs("Girdiginiz plaka bu sehrin bir komsusu degildir.",dosya2);
            break;
        case 6:
            printf("Listelemek istediginiz bolgeyi giriniz.\n");
            fputs("Listelemek istediginiz bolgeyi giriniz.\n",dosya2);
            printf("(Akdeniz:AK,Karadeniz:KA,Marmara:MA,Ege=EG,Dogu Anadolu=DA,Guneydogu Anadolu=GA,Ic Anadolu=IA)\n Seciminiz:");
            fputs("(Akdeniz:AK,Karadeniz:KA,Marmara:MA,Ege=EG,Dogu Anadolu=DA,Guneydogu Anadolu=GA,Ic Anadolu=IA)\n Seciminiz:",dosya2);
            scanf("%s",&bolge);
            fprintf(dosya2,"Seciminiz:%s",bolge);
            liste=ilk;
            while(liste!=NULL)
            {
                if(strcmp(liste->bolge,bolge)==0)
                {
                    printf("Sehrin adi:%s \t",liste->isim);
                    fprintf(dosya2,"Sehrin adi:%s \t",liste->isim);
                    printf("Sehrin plaka:%d \t",liste->plaka);
                    fprintf(dosya2,"Sehrin plaka:%d \t",liste->plaka);
                    printf("Sehrin komsu sayisi: %d \n",liste->komsusayisi);
                    fprintf(dosya2,"Sehrin komsu sayisi: %d \n",liste->komsusayisi);
                }
                liste=liste->next;
            }

            break;
        case 7:
            printf("Arama kriteriniz fazla icinse 'fazla',esit icinse 'esit',az icinse 'az' yaziniz:\n");
            fputs("Arama kriteriniz fazla icinse 'fazla',esit icinse 'esit',az icinse 'az' yaziniz:\n",dosya2);
            printf("Seciminiz:");
            scanf("%s",&ara);
            fprintf(dosya2,"Seciminiz: %s",ara);
            if(strcmp(ara,"fazla")==0)
            {
                printf("Hangi sayidan fazla?");
                scanf("%d",&secim);
                fputs("Hangi sayidan fazla?\n",dosya2);
                fprintf(dosya2,"%Seciminiz:%d\n",secim);
                liste=ilk;
                while(liste!=NULL)
                {
                    if(liste->komsusayisi>secim)
                    {
                        printf("%s:%d \n",liste->isim,liste->komsusayisi);
                        fprintf(dosya2,"%s:%d \n",liste->isim,liste->komsusayisi);
                    }
                    liste=liste->next;
                }
            }
            else if(strcmp(ara,"esit")==0)
            {
                printf("Hangi sayiya esit?");
                scanf("%d",&secim);
                fputs("Hangi sayiya esit?\n",dosya2);
                fprintf(dosya2,"Seciminiz:%d\n",secim);
                liste=ilk;
                while(liste!=NULL)
                {
                    if(liste->komsusayisi==secim)
                    {
                        printf("%s:%d \n",liste->isim,liste->komsusayisi);
                        fprintf(dosya2,"%s:%d \n",liste->isim,liste->komsusayisi);
                    }
                    liste=liste->next;
                }
            }
            else if(strcmp(ara,"az")==0)
            {
                printf("Hangi sayidan az?");
                scanf("%d",&secim);
                fputs("Hangi sayidan az?\n",dosya2);
                fprintf(dosya2,"Seciminiz:%d\n",secim);
                liste=ilk;
                while(liste!=NULL)
                {
                    if(liste->komsusayisi<secim)
                    {
                        printf("%s:%d \n",liste->isim,liste->komsusayisi);
                        fprintf(dosya2,"%s:%d \n",liste->isim,liste->komsusayisi);
                    }
                    liste=liste->next;
                }
            }
            else
            {
                printf("Yanlis kriter girdiniz");
                fputs("Yanlis kriter girdiniz.\n\n",dosya2);
            }

            break;
        case 8:
            liste=ilk;
            int max,min,sayi,i;
            int sehirplaka[10];
            char sehirisim[10][20];
            printf("Sirasiyla min ve max komsu sayisi degerlerini giriniz."); scanf("%d%d",&min,&max);
            fputs("Sirasiyla min ve max komsu sayisi degerlerini giriniz.\n",dosya2);
            fprintf(dosya2,"Verdiginiz aralik: %d-%d\n",min,max);
            printf("Kac adet komsu sehir gireceksiniz ?"); scanf("%d",&sayi);
            fputs("Kac adet komsu sehir gireceksiniz ?\n",dosya2);
            fprintf(dosya2,"Sehir sayi seciminiz: %d\n",sayi);
            fputs("Girdiginiz sehirler:\n",dosya2);
            for(i=0;i<sayi;i++){
                    printf("%d. sehri giriniz: ",i+1); scanf("%s",sehirisim[i]);
                    fprintf(dosya2,"%d) %s\n",i+1,sehirisim[i]);
            }
            i=0;
            int saysehir=0;
            while(saysehir<sayi){
            while(liste!=NULL){
                if(strcmp(sehirisim[i],liste->isim)==0){
                    sehirplaka[i]=liste->plaka;
                    i++;
                    saysehir++;
                }
                liste=liste->next;
            }
            liste=ilk;
            }
            int j,k,tempsay,saykomsu=0,saykomsu1=0;
            for(j=0;j<i-1;j++){
                for(k=0;k<i-1-j;k++){
                    if(sehirplaka[k]>sehirplaka[k+1]){
                        tempsay=sehirplaka[k];
                        sehirplaka[k]=sehirplaka[k+1];
                        sehirplaka[k+1]=tempsay;
                    }
                }
            }
            liste=ilk;
            while(liste!=NULL){
                if(liste->komsusayisi>min && liste->komsusayisi<max){
                        saykomsu=0;
                    struct node1 *komsular=liste->komsu;
                    while(komsular!=NULL){
                    for(j=0;j<i;j++){
                     if(komsular->plaka==sehirplaka[j]){
                        saykomsu++;
                        if(saykomsu==sayi){
                                  saykomsu1++;
                         printf("%s \n",liste->isim);
                         fprintf(dosya2,"%s \n",liste->isim); }
                     }
                    }
                     komsular=komsular->next1;

                    }
                }
                liste=liste->next;
            }
            if(saykomsu1==0){
                printf("Ortak komsulari bulunmamaktadir.");
                fputs("Ortak komsulari bulunmamaktadir.",dosya2);
            }

            break;
        case 9:
            liste=ilk;
            yaz(liste,dosya2);
            break;
        case 10:
            printf("Program sonlandi.");
            fputs("Program sonlandi",dosya2);
            exit(1);
        default:
            printf("Hatali secim girdiniz.\n");
            fputs("Hatali secim girdiniz.\n",dosya2);
        }
    }

    return 0;
}
