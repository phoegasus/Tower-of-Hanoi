#include <stdio.h>
#include <stdlib.h>

//Projet langage C par Lakhlifi Omar

typedef struct tour
{
	int etage[9];
	int sommet;
} tour;

typedef struct joueur
{
	char nom[10];
	int mouvements;
} joueur;

void affichage_tours(int taille, tour t1, tour t2, tour t3) //affiche les piles
{
	int i;
	for(i=(taille-1);i>=0;i--)
		printf("\t\t%d\t\t\t%d\t\t\t%d\n",t1.etage[i],t2.etage[i],t3.etage[i]);
}

void affichage_infos(int mouvements, int record) //affiche les informations
{
	printf("\n\nControles (en majuscule) :\nQ : 1 -> 2\tS : 1 -> 3\tD : 2 -> 1\tF : 2 -> 3\tG : 3 -> 1\tH : 3 -> 2\n\nE : Enregistrer\n\nMouvements effectues : %d\t\t\t\t\t\t\t\t\t\t\t\tMeilleur record : %d\n\n", mouvements, record);
}

void affichage_fin(int mouvements, char nom[])
{
	char choix;
	printf("Felicitations %s, vous avez gagne !\n\nObjectif atteint en %d mouvements.\n\n", nom, mouvements);
	system("pause");
	system("cls");
	printf("Que voulez-vous faire ?\n\n\n1.Menu Principal\n\n2.Quitter");
	do
	choix = getch();
	while (choix!='1'&&choix!='2');
	switch(choix)
	{
		case '1': //retour au main
				  break;
		
		case '2': system("exit");
				  break;
	}
}

//Projet langage C par Lakhlifi Omar

void nom_joueur(joueur* j)
{
	printf("Veuillez entrer votre nom : ");
	gets(j->nom);
}

int enregistrer_partie(tour* t1, tour* t2, tour* t3, joueur* j, int taille)
{
	int i;
	char choix;
	system("cls");
	FILE* p = fopen("./data/save.bin","rb");
	if(p!=0)
	{
		printf("\n\n\nUne sauvegarde existe deja, voulez-vous l'ecraser ?\n\n\n1.Oui\n\n2.Non");
		do
			choix = getch();
		while(choix!='1'&&choix!='2');
		switch(choix)
		{
			case '1': p = fopen("./data/save.bin","wb");
					fwrite(&taille,sizeof(int),1,p);
					fwrite(&j->mouvements,sizeof(int),1,p)
					for(i=taille-1;i>=0;i--)
						fwrite(&t1->etage[i],sizeof(int),1,p);
					for(i=taille-1;i>=0;i--)
						fwrite(&t2->etage[i],sizeof(int),1,p);
					for(i=taille-1;i>=0;i--)
						fwrite(&t3->etage[i],sizeof(int),1,p);
					fclose(p);
					system("cls");
					printf("\n\n\nPartie enregistree.\n\n1.Continuer la partie\n\n2.Menu Principal");
					do
						choix = getch();
					while(choix!='1'&&choix!='2');
					switch(choix)
					{
						case '1': return 0;
								  break;
								  
						case '2': return 1;
								  break;
					}
					break;
			
			case '2': return 0;
					break;
		}
	}
	else
	{
		p = fopen("./data/save.bin","wb");
		fwrite(&taille,sizeof(int),1,p);
		for(i=taille-1;i>=0;i--)
			fwrite(&t1->etage[i],sizeof(int),1,p);
		for(i=taille-1;i>=0;i--)
			fwrite(&t2->etage[i],sizeof(int),1,p);
		for(i=taille-1;i>=0;i--)
			fwrite(&t3->etage[i],sizeof(int),1,p);
		fclose(p);
		system("cls");
		printf("\n\n\nPartie enregistree.\n\n1.Continuer la partie\n\n2.Menu Principal");
		do
			choix = getch();
		while(choix!='1'&&choix!='2');
		switch(choix)
		{
			case '1': return 0;
					  break;
								  
			case '2': return 1;
					  break;
		}
	}
}

//Projet langage C par Lakhlifi Omar

void explication()
{
	int i;
	system("cls");
	printf("\t\t\t\t\t\t\tEXPLICATION\n\n\nOn commence avec trois piles de chiffres, presentees de la maniere suivante (0 = vide) :\n\n");
	for(i=1;i<=4;i++)
		printf("\t\t%d\t\t\t0\t\t\t0\n",i);
	printf("\nL'objectif est de deplacer tous les chiffres de la pile 1 vers la pile 3 en s'aidant de la pile 2, tout en respectant les regles suivantes :\n\n- On ne peut bouger qu'un seul numero par etape et cela doit toujours etre celui qui se trouve au sommet.\n\n- L'ordre des chiffres d'une pile doit toujours etre croissant du haut vers le bas.\n\n\n\t\t\t\t\t\tControles (en majuscule) :\n\n\tQ : 1 -> 2\tS : 1 -> 3\tD : 2 -> 1\tF : 2 -> 3\tG : 3 -> 1\tH : 3 -> 2\n\n");
	system("pause");
}

int meilleur_record(int record, int taille)
{
	if(taille==4)
	{
		FILE* p_record = fopen("./data/record.bin","rb");
		int x;
		fread(&x,sizeof(int),1,p_record);
		if(x==0)
		{
			p_record = fopen("./data/record.bin","wb");
			rewind(p_record);
			fwrite(&record,sizeof(int),1,p_record);
			fclose(p_record);
			return record;
		}
		else if(x>0)
			if(record<x)
			{
				p_record = fopen("./data/record.bin","wb");
				rewind(p_record);
				fwrite(&record,sizeof(int),1,p_record);
				fclose(p_record);
				return record;
			}
		else
			return x;
	}
	else
	{
		FILE* p_record = fopen("./data/record_diff.bin","rb");
		int x;
		fread(&x,sizeof(int),1,p_record);
		if(x==0)
		{
			p_record = fopen("./data/record_diff.bin","wb");
			rewind(p_record);
			fwrite(&record,sizeof(int),1,p_record);
			fclose(p_record);
			return record;
		}
		else if(x>0)
			if(record<x)
			{
				p_record = fopen("./data/record_diff.bin","wb");
				rewind(p_record);
				fwrite(&record,sizeof(int),1,p_record);
				fclose(p_record);
				return record;
			}
		else
			return x;
	}
}

//Projet langage C par Lakhlifi Omar

void charger_partie(FILE* p, int record, int record_diff)
{
	int taille;
	fread(&taille,sizeof(int),1,p);
	if(taille==4)
		jeu(taille, record, p);
	else if(taille==9)
		jeu(taille, record_diff, p);
	else
		printf("Erreur");
}

int jeu(int taille, int record, FILE* p) //la fonction qui gere le jeu
{
	system("cls"); //effacer le contenu de la console
	int i;
	joueur j;
	if(p==0)
		nom_joueur(&j);
	char bouton;
	tour tour_1, tour_2, tour_3;
	tour_1.sommet = taille-1;
	tour_2.sommet = 0;
	tour_3.sommet = 0;
	if(p==0)
	{
		int x = taille;
		for(i=0;i<taille;i++)
		{
			tour_1.etage[i] = x;
			x--;
		}
		for(i=0;i<taille;i++)
			tour_2.etage[i] = 0;
		for(i=0;i<taille;i++)
			tour_3.etage[i] = 0;
	}
	else
	{
		for(i=taille-1;i>=0;i--)
			fread(&tour_1.etage[i],sizeof(int),1,p);
		for(i=taille-1;i>=0;i--)
			fread(&tour_2.etage[i],sizeof(int),1,p);
		for(i=taille-1;i>=0;i--)
			fread(&tour_3.etage[i],sizeof(int),1,p);
	}
	if(taille == 4)
		{
			while(tour_3.etage[0]!=4 || tour_3.etage[1]!=3 || tour_3.etage[2]!=2 || tour_3.etage[3]!=1) //tant qu'on n'a pas atteint l'objectif
			{
				system("cls");
				affichage_infos(j.mouvements, record);
				affichage_tours(taille, tour_1, tour_2, tour_3);
				do
					bouton = getch();
				while(bouton!='Q'&&bouton!='S'&&bouton!='D'&&bouton!='F'&&bouton!='G'&&bouton!='H'&&bouton!='E');
				switch(bouton)
				{
					case 'Q': 	if(tour_1.sommet!=0||tour_1.etage[tour_1.sommet]!=0) //si la pile source n'est pas vide
								{	//si la pile destination respecte les règles
									if((tour_2.etage[tour_2.sommet]!=0&&tour_1.etage[tour_1.sommet]<tour_2.etage[tour_2.sommet])||tour_2.etage[tour_2.sommet]==0)
									{	//si la pile destination est vide, ne pas incrémenter l'indice du sommet
										if(tour_2.etage[tour_2.sommet] != 0)
											tour_2.sommet++;
										tour_2.etage[tour_2.sommet] = tour_1.etage[tour_1.sommet];
										tour_1.etage[tour_1.sommet] = 0;
										if(tour_1.sommet != 0)
											tour_1.sommet--;
										j.mouvements++;	
									}
								} 
								break;
					case 'S': 	if(tour_1.sommet!=0||tour_1.etage[tour_1.sommet]!=0)
								{
									if((tour_3.etage[tour_3.sommet]!=0&&tour_1.etage[tour_1.sommet]<tour_3.etage[tour_3.sommet])||tour_3.etage[tour_3.sommet]==0)
									{
										if(tour_3.etage[tour_3.sommet] != 0)
											tour_3.sommet++;
										tour_3.etage[tour_3.sommet] = tour_1.etage[tour_1.sommet];
										tour_1.etage[tour_1.sommet] = 0;
										if(tour_1.sommet != 0)
											tour_1.sommet--;
										j.mouvements++;
									}
								} 
								break;
					case 'D': 	if(tour_2.sommet!=0||tour_2.etage[tour_2.sommet]!=0)
								{
									if((tour_1.etage[tour_1.sommet]!=0&&tour_2.etage[tour_2.sommet]<tour_1.etage[tour_1.sommet])||tour_1.etage[tour_1.sommet]==0)
									{
										if(tour_1.etage[tour_1.sommet] != 0)
											tour_1.sommet++;
										tour_1.etage[tour_1.sommet] = tour_2.etage[tour_2.sommet];
										tour_2.etage[tour_2.sommet] = 0;
										if(tour_2.sommet != 0)
											tour_2.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'F': 	if(tour_2.sommet!=0||tour_2.etage[tour_2.sommet]!=0)
								{
									if((tour_3.etage[tour_3.sommet]!=0&&tour_2.etage[tour_2.sommet]<tour_3.etage[tour_3.sommet])||tour_3.etage[tour_3.sommet]==0)
									{	
										if(tour_3.etage[tour_3.sommet] != 0)
											tour_3.sommet++;
										tour_3.etage[tour_3.sommet] = tour_2.etage[tour_2.sommet];
										tour_2.etage[tour_2.sommet] = 0;
										if(tour_2.sommet != 0)
											tour_2.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'G': 	if(tour_3.sommet!=0||tour_3.etage[tour_3.sommet]!=0)
								{
									if((tour_1.etage[tour_1.sommet]!=0&&tour_3.etage[tour_3.sommet]<tour_1.etage[tour_1.sommet])||tour_1.etage[tour_1.sommet]==0)
									{
										if(tour_1.etage[tour_1.sommet] != 0)
											tour_1.sommet++;
										tour_1.etage[tour_1.sommet] = tour_3.etage[tour_3.sommet];
										tour_3.etage[tour_3.sommet] = 0;
										if(tour_3.sommet != 0)
											tour_3.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'H': 	if(tour_3.sommet!=0||tour_3.etage[tour_3.sommet]!=0)
								{
									if((tour_2.etage[tour_2.sommet]!=0&&tour_3.etage[tour_3.sommet]<tour_2.etage[tour_2.sommet])||tour_2.etage[tour_2.sommet]==0)
									{
										if(tour_2.etage[tour_2.sommet] != 0)
											tour_2.sommet++;
										tour_2.etage[tour_2.sommet] = tour_3.etage[tour_3.sommet];
										tour_3.etage[tour_3.sommet] = 0;
										if(tour_3.sommet != 0)
											tour_3.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'E':	if(enregistrer_partie(&tour_1, &tour_2, &tour_3, taille)==1)
									return;
								break;
				}
			}
			system("cls");
			affichage_infos(j.mouvements, meilleur_record(j.mouvements, taille));
			affichage_tours(taille, tour_1, tour_2, tour_3);
			affichage_fin(j.mouvements, j.nom);
		}
		else
		{
			while(tour_3.etage[0]!=9 || tour_3.etage[1]!=8 || tour_3.etage[2]!=7 || tour_3.etage[3]!=6 || tour_3.etage[4]!=5 || 
		      	  tour_3.etage[5]!=4 || tour_3.etage[6]!=3 || tour_3.etage[7]!=2 || tour_3.etage[8]!=1)
			{
				system("cls");
				affichage_infos(j.mouvements, record);
				affichage_tours(taille, tour_1, tour_2, tour_3);
				do
					bouton = getch();
				while(bouton!='Q'&&bouton!='S'&&bouton!='D'&&bouton!='F'&&bouton!='G'&&bouton!='H'&&bouton!='E');
				switch(bouton)
				{
					case 'Q': 	if(tour_1.sommet!=0||tour_1.etage[tour_1.sommet]!=0) //si la pile source n'est pas vide
								{	//si la pile destination respecte les règles
									if((tour_2.etage[tour_2.sommet]!=0&&tour_1.etage[tour_1.sommet]<tour_2.etage[tour_2.sommet])||tour_2.etage[tour_2.sommet]==0)
									{	//si la pile destination est vide, ne pas incrémenter l'indice du sommet
										if(tour_2.etage[tour_2.sommet] != 0)
											tour_2.sommet++;
										tour_2.etage[tour_2.sommet] = tour_1.etage[tour_1.sommet];
										tour_1.etage[tour_1.sommet] = 0;
										if(tour_1.sommet != 0)
											tour_1.sommet--;
										j.mouvements++;	
									}
								} 
								break;
					case 'S': 	if(tour_1.sommet!=0||tour_1.etage[tour_1.sommet]!=0)
								{
									if((tour_3.etage[tour_3.sommet]!=0&&tour_1.etage[tour_1.sommet]<tour_3.etage[tour_3.sommet])||tour_3.etage[tour_3.sommet]==0)
									{
										if(tour_3.etage[tour_3.sommet] != 0)
											tour_3.sommet++;
										tour_3.etage[tour_3.sommet] = tour_1.etage[tour_1.sommet];
										tour_1.etage[tour_1.sommet] = 0;
										if(tour_1.sommet != 0)
											tour_1.sommet--;
										j.mouvements++;
									}
								} 
								break;
					case 'D': 	if(tour_2.sommet!=0||tour_2.etage[tour_2.sommet]!=0)
								{
									if((tour_1.etage[tour_1.sommet]!=0&&tour_2.etage[tour_2.sommet]<tour_1.etage[tour_1.sommet])||tour_1.etage[tour_1.sommet]==0)
									{
										if(tour_1.etage[tour_1.sommet] != 0)
											tour_1.sommet++;
										tour_1.etage[tour_1.sommet] = tour_2.etage[tour_2.sommet];
										tour_2.etage[tour_2.sommet] = 0;
										if(tour_2.sommet != 0)
											tour_2.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'F': 	if(tour_2.sommet!=0||tour_2.etage[tour_2.sommet]!=0)
								{
									if((tour_3.etage[tour_3.sommet]!=0&&tour_2.etage[tour_2.sommet]<tour_3.etage[tour_3.sommet])||tour_3.etage[tour_3.sommet]==0)
									{	
										if(tour_3.etage[tour_3.sommet] != 0)
											tour_3.sommet++;
										tour_3.etage[tour_3.sommet] = tour_2.etage[tour_2.sommet];
										tour_2.etage[tour_2.sommet] = 0;
										if(tour_2.sommet != 0)
											tour_2.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'G': 	if(tour_3.sommet!=0||tour_3.etage[tour_3.sommet]!=0)
								{
									if((tour_1.etage[tour_1.sommet]!=0&&tour_3.etage[tour_3.sommet]<tour_1.etage[tour_1.sommet])||tour_1.etage[tour_1.sommet]==0)
									{
										if(tour_1.etage[tour_1.sommet] != 0)
											tour_1.sommet++;
										tour_1.etage[tour_1.sommet] = tour_3.etage[tour_3.sommet];
										tour_3.etage[tour_3.sommet] = 0;
										if(tour_3.sommet != 0)
											tour_3.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'H': 	if(tour_3.sommet!=0||tour_3.etage[tour_3.sommet]!=0)
								{
									if((tour_2.etage[tour_2.sommet]!=0&&tour_3.etage[tour_3.sommet]<tour_2.etage[tour_2.sommet])||tour_2.etage[tour_2.sommet]==0)
									{
										if(tour_2.etage[tour_2.sommet] != 0)
											tour_2.sommet++;
										tour_2.etage[tour_2.sommet] = tour_3.etage[tour_3.sommet];
										tour_3.etage[tour_3.sommet] = 0;
										if(tour_3.sommet != 0)
											tour_3.sommet--;
										j.mouvements++;
									}
								}
								break;
					case 'E':	if(enregistrer_partie(&tour_1, &tour_2, &tour_3, taille)==1)
									return;
								break;
				}
			}
			system("cls");
			affichage_infos(j.mouvements, meilleur_record(j.mouvements, taille));
			affichage_tours(taille, tour_1, tour_2, tour_3);
			affichage_fin(j.mouvements, j.nom);
		}
}

//Projet langage C par Lakhlifi Omar

void menu()
{
	char choix;
	int record = 0, record_diff = 0;
	system("mkdir data");
	FILE* p_record = fopen("./data/record.bin","rb");
	fread(&record,sizeof(int),1,p_record);
	fclose(p_record);
	p_record = fopen("./data/record_diff.bin","rb");
	fread(&record_diff,sizeof(int),1,p_record);
	fclose(p_record);
	system("cls");
	printf("\n\t\t\t\t\t\t\tMENU\n\n\n1.Nouvelle Partie\n\n2.Charger partie\n\n3.Comment jouer\n\n4.Quitter\n");
	do
		choix = getch();
	while (choix!='1'&&choix!='2'&&choix!='3'&&choix!='4');
	switch(choix)
	{
		case '1': system("cls");
				  printf("\n\n\t\t\t\t\t\t\tDifficulte :\n\n\n1.Facile\n\n2.Difficile\n");
				do
					choix = getch();
				while (choix!='1'&&choix!='2');
				switch(choix)
				{
					case '1': jeu(4, record, 0);
							  break;
					
					case '2': jeu(9, record_diff, 0);
							  break;
				}
				break;
		
		case '2': p_record = fopen("./data/save.bin","rb");
				if(p_record==0)
				{
					fclose(p_record);
					system("cls");
					printf("Sauvegarde introuvable.\n\n");
					system("pause");
				}
				else
					charger_partie(p_record, record, record_diff);
				break;
				
		case '3': explication();
				break;
		
		case '4': system("exit");
	}
}

//Projet langage C par Lakhlifi Omar

main()
{
	while(1)
		menu();
}

//Projet langage C par Lakhlifi Omar
