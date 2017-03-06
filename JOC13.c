/* Amerikkalaiset nopat
Kyseessä on peli jossa pelaajalla on aluksi rahaa 10€,
josta hän asettaa haluamansa panoksen. Tämän jälkeen ohjelma
heittää kahta noppaa ja laskee noppien silmäluvut yhteen

(c) Tuukka Rantahalvari, 2013
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int KysyPanos(int rahamaara);
int HeitaNoppia(int *HeittojenLkm);
int RahojenKasittely(int summa, int panos, int heitot);
int syotteenTarkistus(char merkkijono[]);
int PelinLopetus(int rahat);

int main (void){
/*Pääfunktio, jossa tulostetaan aluksi pelin säännöt. Tämän jälkeen
toistorakenteen sisällä kutsutaan alifunktioita joiden avulla peli toimii*/
int rahat = 10;
int summa;
int panos;
int heitot;
int peli = 2;
	printf("Tervetuloa pelaamaan Amerikkalaisia noppia\nPelissa asetat panoksen ja heitat kahta noppaa,\njoiden silmalukujen summan perusteella maaraytyy voitatko vai haviatko.\nJos heitat ensimmaisella heitolla 7 tai 11 voitat, jos heitat 2, 3 tai 12 haviat.\nMuuten heitat uudelleen kunnes saat uudelleen ensimmaisella kierroksella heittamasi luvun (voitat) tai luvun 7.(haviat)\n");
           while(peli != 0){
	   heitot = 0; 
	   panos = KysyPanos(rahat);
	   summa = HeitaNoppia(&heitot);
	   rahat = (rahat - panos) + RahojenKasittely(summa, panos, heitot);
	   peli = PelinLopetus(rahat);
	}
	

return 0;
}
int KysyPanos(int rahamaara){
/*Funktio, joka saa parametrina pelaajan rahamäärän, kysyy panosta
ja pelaajan syötettyä hyväksyttävän panoksen palauttaa sen.*/
int panostus = 0;
int k = 1;
char jono[200];
		
		while(panostus < 1){
		 k=1;
		 while(k != 0){
                   printf("\nAseta panos (1-%d) > ", rahamaara);
	           fgets(jono, 200, stdin);
	           k = syotteenTarkistus(jono);
	         }
	       panostus = atoi(jono);
		if(panostus > rahamaara){
	       printf("\nSinulla ei ole tarpeeksi rahaa\n");
		panostus= 0;
	       }else if(panostus == 0){
		printf("Panoksen tulee olla > 0\n");	
		}
}
return panostus;
}int HeitaNoppia(int *HeittojenLkm){
/*Funktio joka saa parametrina pääfunktion heitot-muuttujan(int) osoitteen.
Funktiossa arvotaan kahdelle nopalle arvoja väliltä 1-6 ja lasketaan niiden summat yhteen.
Voiton tai häviön tapahtuessa tulostetaan siitä ilmoittava teksti. 
Tarvittaessa useampia heittoja, kirjataan heittojen lkm ylös.
Funktio tallettaa osoittimien avulla pääfunktion heitot-muuttujaan heittojen lukumäärän,
sekä palauttaa voittavan/häviävän summan*/
  int noppa1;
  int noppa2;
  int temp;
  int summa2;
  int i=1;
  int lkm=1;

	srand(time(NULL));
	noppa1=rand() % 6 + 1;
	noppa2=rand()% 6 + 1;
	summa2=noppa1+noppa2;
	temp = summa2;
	printf("Heitit %d ja %d eli yhteensa %d\n", noppa1, noppa2, summa2);
	if(summa2 == 7 || summa2 == 11){
		printf("Onneksi olkoon! Voitit!\n");
		i=0;
		}else if(summa2 == 2 || summa2 == 3 || summa2 == 12){
		    printf("Voi, voi hävisit pelin\n");
		    i=0;
		  }else while(i > 0){
		  noppa1=rand() % 6 + 1;
		  noppa2=rand() % 6 + 1;
		  summa2=noppa1 + noppa2;
		  lkm++;
		  printf("Heitit %d\n", summa2);
		  if(summa2 == temp){
		    printf("Onneksi olkoon, voitit!\n");
		    i=0;
		  }else if(summa2 == 7){
		     printf("Voi voi hävisit\n");
		     i=0;
		  }else
		   printf("Uusi heitto\n");
		} 
	*HeittojenLkm = lkm;
	
return summa2;
}int RahojenKasittely(int summa, int panos, int heitot){
/*Funktio joka saa parametreina panoksen (int), heittyjen noppien silmälukujen summan (int) sekä
heittojen lukumäärän (int) ja näiden perusteella laskee paljonko pelaaja voittaa ja palauttaa 
voittosumman (int)*/
 int voitot=0;
 	if(heitot == 1){
	 switch(summa){
	  case 7: case 11:
	   voitot = panos * 2;
	   printf("Voittosummasi on %d\n", voitot);
	  break;
	  case 2: case 3: case 12:
	  voitot=0;
	  printf("Voittosummasi on %d\n", voitot);
	 break;
	 }
	}else switch(summa){ 
	 case 7:
	  voitot=0;
	  printf("Voittosummasi on %d\n", voitot);
	 break;
	 default:
	  voitot = panos * 2;
	  printf("Voittosummasi on %d\n", voitot);
	 break;	  
	} 

return voitot;
}
int syotteenTarkistus(char merkkijono[]){
/*Funktio saa syötteenä merkkijonon ja sen pituuden, käy läpi merkkijonon
merkit tarkastaen onko joukossa muita kuin kokonaislukuja.*/
int i, j=0;	
	for(i=0; i<strlen(merkkijono); i++){
	if(isalpha(merkkijono[i]) || ispunct(merkkijono[i])){
	 j++;
	}
      }
return j;
}
int PelinLopetus(int rahat){
/*Funktio joka saa syötteen pelaajalla käytössä olevan rahamäärän.
Jos pelaajalla ei ole enää rahaa funktio merkitsee palauttetavan muuttujan arvoksi 0.
Muutoin funktio kysyy pelaajalta haluaako hän jatkaa pelaamista(syötä 1) vai lopettaa(syötä 0),
tarkastaa, että annettu syöte on jompikumpi halutuista kokonaisluvuista. Funktio palauttaa
kokonaislukumuuttajan jonka arvo on joko 1 tai 0*/
int j;
int i = 1;
int peli;
char syote[200];

	if (rahat == 0){
	  peli = 0;
	  i = 0;
	}
	while (i !=0){
	  printf("\nSyota 1 pelataksesi tai 0 lopettaaksesi ");
	  fgets(syote, 200, stdin);
	  j = syotteenTarkistus(syote);
	 if (j == 0){
	  peli = atoi(syote);
	  i = 0;
 	 }if(peli > 1 || peli < 0){
	   printf("virheellinen syote!");
	  }else if(peli == 1){
	      i = 0;
	   }
	 }

return peli;	
}
