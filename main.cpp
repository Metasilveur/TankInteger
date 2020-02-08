#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define nb_ennemi 4

SDL_Surface *ecran;
SDL_Surface *corps, *balle, *arme;
SDL_Surface *corpsT, *balleT, *armeT;
SDL_Surface *terrain, *mur, *murT;
SDL_Surface *mure, *mureT;
SDL_Surface *explosion;
SDL_Surface *wasted;
SDL_Surface *barre, *barreT;
SDL_Surface *roche, *rocheT;
SDL_Surface *victoire;
SDL_Surface *animeau;
SDL_Surface *choix;
SDL_Surface *plouf, *plouft;
SDL_Surface *escargaut;
SDL_Surface *bullete;
SDL_Surface *bullet[360];
SDL_Surface *brule;

SDL_Surface *texte;

SDL_Surface *test[360];
SDL_Surface *test1[5];

SDL_Surface *toast[360];
SDL_Surface *toast1[4];
SDL_Surface *fume[7];
SDL_Surface *fume_anim[7][360];

SDL_Rect hp_pos;
SDL_Rect pos;
SDL_Rect oldpos;
SDL_Rect clipper;
SDL_Rect clipe[81];
SDL_Rect clipe1[6];
SDL_Rect clipe2[6];
SDL_Rect clipe3[10];

SDL_Surface *FT[8];
SDL_Surface *FTA[8][360];

char write[50] = "";

int continuer;
int fin;
int droite, gauche, haut, bas;
int av, ar;
int angle;
int mvtx, mvty;
int canon;
int choixTank = 1;
int feu=0;
int eau=0;
int plante=0;

int jeu=1;

double tx, ty;
double xv, xy;
double px, py;
float longueur;
int ennemi=20;


TTF_Font *police = NULL;

SDL_Color NOIRE ={0,0,0};

struct tank
{
    SDL_Surface *sprite;
    SDL_Surface *sprite2;
    SDL_Rect pos;
    SDL_Rect pos2;
    SDL_Rect oldpos;
    SDL_Rect oldpos2;
    int angle;
    int hp;
    int touche;
};

struct balle
{
    int actif;
    int clique;
    int angle;
    float vecteurx, vecteury;
    float rx, ry;

    SDL_Surface *sprite;
    SDL_Rect pos;
    SDL_Rect oldpos;

    balle *suivant;

    int vitesse;

    int impact;
    int frame_impact;
    int tempo_impact;
    int angle_impact;
    SDL_Rect pos_impact;
};

struct balle tir[50];

struct balle_ennemi
{
    int actif;
    int clique;
    float vecteurx, vecteury;
    float rx, ry;

    SDL_Surface *sprite;
    SDL_Rect pos;
    SDL_Rect oldpos;

    int vitesse;
};

struct balle_ennemi tire[50][nb_ennemi];

//typedef struct Liste Liste;
struct Liste
{
    struct balle *premier;
};

struct obstacle
{
   SDL_Surface *sprite;
   SDL_Rect pos;
   SDL_Rect oldpos;

   int hp;
};

struct obstacle caillou[4];

struct mur
{
    SDL_Surface *sprite;
    SDL_Surface *sprite2;
    SDL_Rect pos;
    SDL_Rect pos2;
    SDL_Rect oldpos;
    SDL_Rect oldpos2;
    SDL_Rect mort;

    int angle;
    int av, ar;
    int hp;
    int frame;
    int explo;
    int actif;
    float vecteurx, vecteury;

    int ralentit;
    int lent;

    int tps_tir; // pour son aléatoire de merde

    int brulure;
    int brulure1;
    int brulure2;
    int brulure3;
    int brulure4;
    int Temps_brulure;

    SDL_Rect moneret;
};

struct mur pierre[nb_ennemi];

SDL_Rect posT;

struct titi
{
    SDL_Surface *sprite;
    SDL_Rect pos;
    int hp;
};

struct titi Titi;

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    //SDL_EnableKeyRepeat(10,10);

    police = TTF_OpenFont("arial.ttf",25);

    texte = TTF_RenderText_Solid(police, write, NOIRE);

    corps = new SDL_Surface;
    corpsT = new SDL_Surface;
    arme = new SDL_Surface;
    armeT = new SDL_Surface;
    balle = new SDL_Surface;
    balleT = new SDL_Surface;
    mur = new SDL_Surface;
    murT = new SDL_Surface;
    mure = new SDL_Surface;
    mureT = new SDL_Surface;
    terrain = new SDL_Surface;
    explosion = new SDL_Surface;

    //corps = IMG_Load("corpsE.png");
    //arme = IMG_Load("armeE.png");
    //animeau = IMG_Load("anifeu.png");
    balle = IMG_Load("balle.png");
    terrain = IMG_Load("TerrainNeige.png");
    mur = IMG_Load("corpsR111.png");
    mure = IMG_Load("armeR111.png");
    explosion = IMG_Load("explosion.png");
    barre = IMG_Load("hp_bar.png");
    wasted = IMG_Load("wasted.png");
    roche = IMG_Load("caillou.png");
    victoire = IMG_Load("victoire.png");
    escargaut = IMG_Load("slow.png");
    bullete = IMG_Load("bullet.png");
    choix = IMG_Load("choix.png");

    brule = IMG_Load("brule.png");

    FT[0] = IMG_Load("bou1.png");
    FT[1] = IMG_Load("bou2.png");
    FT[2] = IMG_Load("bou3.png");
    FT[3] = IMG_Load("bou4.png");
    FT[4] = IMG_Load("bou5.png");
    FT[5] = IMG_Load("bou6.png");
    FT[6] = IMG_Load("bou7.png");
    FT[7] = IMG_Load("bou8.png");


    for(int i=0;i<8;i++)
    {
        for(int j=0;j<360;j++)
        {
            FTA[i][j] = rotozoomSurface(FT[i], j, 1,1);
        }
    }

    /*
    fume[0] = IMG_Load("fume1.png");
    fume[1] = IMG_Load("fume2.png");
    fume[2] = IMG_Load("fume3.png");
    fume[3] = IMG_Load("fume4.png");
    fume[4] = IMG_Load("fume5.png");
    fume[5] = IMG_Load("fume6.png");
    fume[6] = IMG_Load("fume7.png");

    for(int i=0;i<7;i++)
    {
        for(int j=0;j<360;j++)
        {
            fume_anim[i][j] = rotozoomSurface(fume[i], j, 1,1);
        }
    }*/

    barreT = rotozoomSurface(barre, 0,0.2,1);
    //corpsT = rotozoomSurface(corps,0,0.3,1);
    //armeT =  rotozoomSurface(arme,0,0.3,1);
    murT = rotozoomSurface(mur,0,0.3,1);
    mureT = rotozoomSurface(mure,0,0.3,1);

    balleT =  rotozoomSurface(balle,0,0.3,1);


    /*for(int i=0;i<360;i++)
    {
        bullet[i] = rotozoomSurface(bullete,i,1,1);
    }*/

   /* for(int i=0;i<360;i++)
    {
        test[i] = rotozoomSurface(arme,i,0.3,1);
    }

    for(int i=0;i<4;i++)
    {
        test1[i] = rotozoomSurface(corps,i*90,0.3,1);
    }*/

    for(int i=0;i<360;i++)
    {
        toast[i] = rotozoomSurface(mure,i,1,1);
    }

    for(int i=0;i<4;i++)
    {
        toast1[i] = rotozoomSurface(mur,i*90,1,1);
    }

    pos.x = 0;
    pos.y = 0;
    pos.w = 100;
    pos.h = 100;

    hp_pos.x = 0;
    hp_pos.y = 400;

    posT.x = 0;
    posT.y = 0;
    posT.w = 800;
    posT.h = 35;

    droite = gauche = haut = bas =0;
    px=py=0;
    continuer=1;
    fin=1;
    canon=0;
    av =1;
    ar =0;

    ecran = SDL_SetVideoMode(915,552, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //ecran = SDL_SetVideoMode(1920,1080, 32, SDL_HWSURFACE  | SDL_FULLSCREEN);
    //SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));

    SDL_Flip(ecran);
}

void init_joueur(struct tank* sp)
{
    sp->sprite = corpsT;
    sp->sprite2 = armeT;

    sp->pos.x = 0;
    sp->pos.y = 0;

    sp->pos2.x = -9;
    sp->pos2.y = -6;

    if(feu==1)
    {
        sp->hp = 150;
    }
    if(eau==1)
    {
        sp->hp = 200;
    }
    if(plante==1)
    {
        sp->hp = 100;
    }
    sp->hp = 1000;
    sp->touche = 0;
}

void init_tir(struct balle *sp)
{
    sp->sprite = balleT;
    sp->actif=0;
    sp->clique=0;

    sp->impact=0;
    sp->frame_impact=0;
    sp->tempo_impact=0;
}

void init_obstacle(struct obstacle *sp, int x, int y)
{
        sp->sprite = roche;
        sp->pos.x = x;
        sp->pos.y = y;
        sp->hp = 3;
}

void init_tir_ennemi(struct balle_ennemi *sp)
{
    sp->sprite = balleT;
    sp->actif=0;
    sp->clique=0;
}
/*
void init_titi(struct titi *sp)
{
    sp->sprite = oiseau;
    sp->pos.x = 500;
    sp->pos.y = 500;
    sp->hp = 5;
}*/

struct Liste *initialisation()
{
    struct Liste *liste = (struct Liste*)malloc(sizeof(*liste));
    struct balle *Balle = (struct balle*)malloc(sizeof(*Balle));

    Balle->suivant = NULL;
    liste->premier = Balle;

    return liste;
}

void init_mur(struct mur *sp)
{
    sp->sprite = murT;
    sp->sprite2 = mureT;
    sp->av =1;
    sp->ar =0;
    sp->hp=50;

    sp->frame=0;
    sp->explo=0;
    sp->actif=0;
    sp->ralentit=0;
    sp->lent=0;

    sp->brulure=0;
    sp->brulure1=0;
    sp->brulure2=0;
    sp->brulure3=0;
    sp->brulure4=0;

    sp->tps_tir=rand()%80;

    sp->Temps_brulure=0;
}

void init_mur2(struct mur *sp)
{
    sp->sprite = murT;
    sp->sprite2 = mureT;
    sp->av =0;
    sp->ar =1;
    sp->hp=3;

    sp->frame=0;
    sp->explo=0;
}

bool collision(SDL_Rect A, SDL_Rect B, SDL_Surface *AS, SDL_Surface *BS)
{
    int AW, AH, BW, BH;

    AW = AS->w;
    AH = AS->h;
    BW = BS->w;
    BH = BS->h;

    if((A.x >= B.x + BW)
       || (A.x + AW <= B.x)
       || (A.y >= B.y + BH)
       || (A.y + AH <= B.y))
            return false;
        else
            return true;
}

void add_tank(struct mur *sp)
{
    if(sp->actif==1)
    {
        int cote;
        int posi;

        //random = rand()%6;
        cote = rand()%2;

        sp->frame = 0;
        sp->hp = 50;
        sp->ralentit=0;
        sp->lent=0;
        sp->brulure=0;
        sp->brulure1=0;
        sp->brulure2=0;
        sp->brulure3=0;
        sp->brulure4=0;
        sp->Temps_brulure=0;

        if(cote==0)
        {
            posi = rand()%500;

            sp->pos.x = -100;
            sp->pos.y = posi;
            sp->av=1;
            sp->ar=0;
        }

        if(cote==1)
        {
            posi = rand()%500;

            sp->pos.x = 1050;
            sp->pos.y = posi;
            sp->av=0;
            sp->ar=1;
        }
        sp->actif=0;
    }
}

int zbeub=0;

void depla_suit(struct mur *sp, struct tank *spd)
{

    //sp->pos.x = pos.x + R*cos((atan2(mvtx-pos.x-30,pos.y+30-mvty))+29.8)+32;
    //sp->pos.y = pos.y + R*sin((atan2(mvtx-pos.x-30,pos.y+30-mvty))+29.8)+32;

    int dx,dy;
    int tange;
    tange = atan2(sp->pos.x+30-spd->pos.x-30,sp->pos.y+30-spd->pos.y-30)*180/M_PI;

    if(tange<0)
    {
        tange=tange+360;
    }

    sp->angle = tange;


    for(int i =0; i<360;i++)
    {
        if(i==tange)
        {
            sp->sprite2 = toast[i];
        }
    }




    /*if(zbeub>=360)
    {
        zbeub=0;
    }

    sp->sprite2 = toast[zbeub];*/

    sp->angle = zbeub;


    sp->sprite = toast1[1];

    dx = spd->pos.x - sp->pos.x;
    dy = spd->pos.y - sp->pos.y;

    longueur = sqrt(dx*dx + dy*dy);

    if(longueur>200)
    {
        sp->vecteurx =  (dx/longueur);
        sp->vecteury = (dy/longueur);

        if(sp->vecteurx==1.0)
        {
            sp->vecteurx=0.999;
        }

        if(sp->vecteurx==-1.0)
        {
            sp->vecteurx=-0.999;
        }

        if(sp->vecteury==1.0)
        {
            sp->vecteury=0.9;
        }

        if(sp->vecteury==-1.0)
        {
            sp->vecteury=-0.9;
        }

        if(sp->vecteurx<0.5)
        {
            sp->vecteurx+=0.5;
        }

        if(sp->vecteury<0.5)
        {
            sp->vecteury+=0.5;
        }

        sp->pos.x += sp->vecteurx*2;
        sp->pos.y += sp->vecteury*2;

    }
    else if(longueur<170)
    {
        if(sp->pos.x+sp->sprite->w <= spd->pos.x)
        {
            sp->pos.x--;
        }
        if(sp->pos.x >= spd->pos.x+spd->sprite->w)
        {
            sp->pos.x++;
        }
        if(sp->pos.y+sp->sprite->h <= spd->pos.y)
        {
            sp->pos.y--;
        }
        if(sp->pos.y >= spd->pos.y+spd->sprite->h)
        {
            sp->pos.y++;
        }
    }
        sp->pos2.x = sp->pos.x+36 +10- sp->sprite2->w / 2;
        sp->pos2.y = sp->pos.y+36 +10- sp->sprite2->w / 2;
}

void depla_suit_a(struct mur *sp, struct tank *spd)
{

}

void ennemi_mur(struct mur *sp, struct obstacle *spd, struct tank *spdt)
{
    if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
    {
        if((sp->pos.x + sp->sprite->w == spd->pos.x+1)
           ||(sp->pos.x + sp->sprite->w == spd->pos.x+2)
           /*||(sp->pos.x + sp->sprite->w == spd->pos.x+3)*/)
        {
            sp->pos.x--;
            if(spdt->pos.y<=spd->pos.y+spd->sprite->h/2)
            {
                if(sp->vecteury>0)
                {
                    sp->pos.y--;
                }
                if(sp->vecteury>=0.5)
                {
                    sp->pos.y--;
                }
            }
            if(spdt->pos.y>spd->pos.y + spd->sprite->h/2)
            {
                if(sp->vecteury<0.5)
                {
                    sp->pos.y++;
                }
            }
        }
        if((sp->pos.y + sp->sprite->h == spd->pos.y+1)
           ||(sp->pos.y + sp->sprite->h == spd->pos.y+2)
           /*||(sp->pos.y + sp->sprite->h == spd->pos.y+3)*/)
        {
            sp->pos.y--;
            if(spdt->pos.x<=spd->pos.x + spd->sprite->w/2)
            {
                if(sp->vecteurx>0)
                {
                    sp->pos.x--;
                }
                if(sp->vecteurx>=0.5)
                {
                    sp->pos.x--;
                }
            }
        }
        if((sp->pos.x == spd->pos.x + spd->sprite->w-1)
           ||(sp->pos.x  == spd->pos.x+ spd->sprite->w-2)
           /*||(sp->pos.x  == spd->pos.x+ spd->sprite->w-3)*/)
        {
            sp->pos.x++;
            if(spdt->pos.y<=spd->pos.y+spd->sprite->h/2)
            {
                if(sp->vecteury>0)
                {
                    sp->pos.y--;
                }
                if(sp->vecteury>=0.5)
                {
                    sp->pos.y--;
                }
            }

        }
        if((sp->pos.y == spd->pos.y + spd->sprite->h-1)
           ||(sp->pos.y  == spd->pos.y+ spd->sprite->h-2)
           /*||(sp->pos.y  == spd->pos.y+ spd->sprite->h-3)*/)
        {
            sp->pos.y++;
            if(spdt->pos.x<=spd->pos.x + spd->sprite->w/2)
            {
                if(sp->vecteurx>0)
                {
                    sp->pos.x--;
                }
                if(sp->vecteurx>=0.5)
                {
                    sp->pos.x--;
                }
            }
        }
    }
}


void ennemi_ennemi(struct mur *sp, struct mur *spd, struct tank *spdt)
{
    if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
    {
        if((sp->pos.x + sp->sprite->w == spd->pos.x+1)||(sp->pos.x + sp->sprite->w == spd->pos.x+2))
        {
            sp->pos.x--;
            if(spdt->pos.y<=spd->pos.y+spd->sprite->h/2)
            {
                if(sp->vecteury>0)
                {
                    sp->pos.y--;
                }
                if(sp->vecteury>=0.5)
                {
                    sp->pos.y--;
                }
            }
            if(spdt->pos.y>spd->pos.y + spd->sprite->h/2)
            {
                if(sp->vecteury<0.5)
                {
                    sp->pos.y++;
                }
            }
        }
        if((sp->pos.y + sp->sprite->h == spd->pos.y+1)||(sp->pos.y + sp->sprite->h == spd->pos.y+2))
        {
            sp->pos.y--;
            if(spdt->pos.x<=spd->pos.x + spd->sprite->w/2)
            {
                if(sp->vecteurx>0)
                {
                    sp->pos.x--;
                }
                if(sp->vecteurx>=0.5)
                {
                    sp->pos.x--;
                }
            }
        }
        if((sp->pos.x == spd->pos.x + spd->sprite->w-1)||(sp->pos.x  == spd->pos.x+ spd->sprite->w-2))
        {
            sp->pos.x++;
            if(spdt->pos.y<=spd->pos.y+spd->sprite->h/2)
            {
                if(sp->vecteury>0)
                {
                    sp->pos.y--;
                }
                if(sp->vecteury>=0.5)
                {
                    sp->pos.y--;
                }
            }

        }
        if((sp->pos.y == spd->pos.y + spd->sprite->h-1)||(sp->pos.y  == spd->pos.y+ spd->sprite->h-2))
        {
            sp->pos.y++;
            if(spdt->pos.x<=spd->pos.x + spd->sprite->w/2)
            {
                if(sp->vecteurx>0)
                {
                    sp->pos.x--;
                }
                if(sp->vecteurx>=0.5)
                {
                    sp->pos.x--;
                }
            }
        }
    }
}

void depla_mur(struct mur *sp, SDL_Rect R)
{
    int tange;
    tange = atan2(sp->pos.x+30-R.x,sp->pos.y+30-R.y)*180/M_PI;

    if(tange<0)
    {
        tange=tange+360;
    }

    sp->angle = tange;

     for(int i =0; i<360;i++)
    {
        if(i==tange)
        {
            sp->sprite2 = toast[i];
        }
    }

    if(sp->av==1)
    {
        sp->pos.x++;
        sp->sprite = toast1[3];
        if(sp->pos.x>=ecran->w-200)
        {
            sp->av=0;
            sp->ar=1;
        }
    }

    if(sp->ar==1)
    {
        sp->pos.x--;
        sp->sprite = toast1[1];
        if(sp->pos.x<=100)
        {
            sp->av=1;
            sp->ar=0;
        }
    }

    //sp->sprite = rotozoomSurface(mur, angle1, 0.3,1);
    //sp->sprite2 = rotozoomSurface(mure, (atan2(sp->pos.x+30-R.x,sp->pos.y+30-R.y)*180/M_PI), 0.3,1);

    sp->pos2.x = sp->pos.x+36 - sp->sprite2->w / 2;
    sp->pos2.y = sp->pos.y+36 - sp->sprite2->w / 2;
}

void deplaJ(struct tank* sp)
{
    int tang;

    tang = atan2(sp->pos.x+30+20-mvtx,sp->pos.y+30+20-mvty)*180/M_PI;

    if(tang<0)
    {
        tang=tang+360;
    }

    sp->angle=tang;

    for(int i =0; i<360;i++)
    {
        if(i==tang)
        {
            sp->sprite2 = test[i];
        }
    }
        if(sp->pos.x>ecran->w-sp->sprite->w)
        {
            sp->pos.x=ecran->w-sp->sprite->w;
        }
    if((sp->pos.x>=0)&&(sp->pos.x<=ecran->w-sp->sprite->w)&&(sp->pos.y>=0)&&(sp->pos.y<=ecran->h-sp->sprite->h))
    {

    if(droite==1)
    {
        sp->pos.x=sp->pos.x+1;

        if(sp->pos.x>ecran->w-sp->sprite->w)
        {
            sp->pos.x=ecran->w-sp->sprite->w;
        }

        sp->sprite = test1[3];
        angle = 270;
    }
    if(gauche==1)
    {
        sp->pos.x=sp->pos.x-1;

        if(sp->pos.x<0)
        {
            sp->pos.x=0;
        }

        sp->sprite = test1[1];
        angle = 90;
    }
    if(haut==1)
    {
        sp->pos.y=sp->pos.y-1;

        if(sp->pos.y<0)
        {
            sp->pos.y=0;
        }

        sp->sprite = test1[0];
        angle = 0;
    }
    if(bas==1)
    {
        sp->pos.y=sp->pos.y+1;

        if(sp->pos.y>ecran->h-sp->sprite->h)
        {
            sp->pos.y=ecran->h-sp->sprite->h;
        }

        sp->sprite = test1[2];
        angle = 180;
    }

    }

    //corpsT = rotozoomSurface(corps, angle, 0.3,1);
    //armeT = rotozoomSurface(arme,tang , 0.3,1);
   // if((eau==1)||(feu==1))
  //  {
        sp->pos2.x = sp->pos.x+46 - sp->sprite2->w / 2;
        sp->pos2.y = sp->pos.y+46 - sp->sprite2->w / 2;
   // }
   // else
   // {
       // sp->pos2.x = sp->pos.x+36 - sp->sprite2->w / 2;
       // sp->pos2.y = sp->pos.y+36 - sp->sprite2->w / 2;
    //}

}

void clip(SDL_Rect OLD, SDL_Surface *terrain, SDL_Surface *sprite)
{
    SDL_Rect posTerrainT;

    clipper.h = sprite->h;
    clipper.w = sprite->w;

    clipper.x = OLD.x;
    clipper.y = OLD.y;

    SDL_SetClipRect(ecran, &clipper);

    posTerrainT.x = pos.x;
    posTerrainT.y = pos.y;

    SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);
}

void clip1(SDL_Rect OLD, SDL_Surface *terrain, SDL_Surface *sprite)
{
    SDL_Rect posTerrainT;

    clipper.h = sprite->h+100;
    clipper.w = sprite->w+100;

    clipper.x = OLD.x;
    clipper.y = OLD.y;

    SDL_SetClipRect(ecran, &clipper);

    posTerrainT.x = pos.x;
    posTerrainT.y = pos.y;

    SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);
}

void clip_anim(SDL_Rect OLD, SDL_Surface *terrain, int a, int b)
{
    SDL_Rect posTerrainT;

    clipper.h = a;
    clipper.w = b;

    clipper.x = OLD.x;
    clipper.y = OLD.y;

    SDL_SetClipRect(ecran, &clipper);

    posTerrainT.x = pos.x;
    posTerrainT.y = pos.y;

    SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);
}

void affiche(SDL_Rect pos, SDL_Surface *sprite)
{
    SDL_Rect posTankT;

    SDL_SetClipRect(ecran, NULL);

    posTankT.x = pos.x;
    posTankT.y = pos.y;

    SDL_BlitSurface(sprite, NULL, ecran, &posTankT);
}

void affiche_anim(SDL_Rect pos, SDL_Surface *sprite, SDL_Rect clip[], int t)
{
    SDL_Rect posTankT;

    SDL_SetClipRect(ecran, NULL);

    posTankT.x = pos.x;
    posTankT.y = pos.y;

    SDL_BlitSurface(sprite, &clip[t], ecran, &posTankT);
}

void tir_joueur(struct balle *sp, SDL_Rect pos, int R)
{
    if(sp->clique==1)
    {
        sp->impact=1;

        sp->pos_impact.x=pos.x + 2*R*cos((atan2(mvtx-pos.x-30-20,pos.y+30+20-mvty))+29.8)+12;
        sp->pos_impact.y=pos.y+ 2*R*sin((atan2(mvtx-pos.x-30-20,pos.y+30+20-mvty))+29.8)+12;

        /*sp->angle = atan2(sp->pos.x+30-20-mvtx,sp->pos.y+30+20-mvty)*180/M_PI;

        if(sp->angle<0)
        {
            sp->angle=sp->angle+360;
        }*/

        sp->angle = (atan2(pos.x+30+20-mvtx,pos.y+30+20-mvty)*180/M_PI)+90;

        if(sp->angle<0)
        {
            sp->angle=sp->angle+360;
        }

        /*
        sp->pos.x = pos.x + R*cos((atan2(mvtx-pos.x-30,pos.y+30-mvty))+29.8)+32;
        sp->pos.y = pos.y + R*sin((atan2(mvtx-pos.x-30,pos.y+30-mvty))+29.8)+32;*/

        sp->pos.x = pos.x + R*cos((atan2(mvtx-pos.x-30-20,pos.y+30+20-mvty))+29.8)+39;
        sp->pos.y = pos.y + R*sin((atan2(mvtx-pos.x-30-20,pos.y+30+20-mvty))+29.8)+39;

        sp->rx = sp->pos.x;
        sp->ry = sp->pos.y;

        tx = mvtx;
        ty = mvty;

        xv = tx - sp->pos.x;
        xy = ty - sp->pos.y;

        longueur = sqrt(xv*xv + xy*xy);

        sp->vecteurx =  (xv/longueur);
        sp->vecteury = (xy/longueur);

        sp->clique=0;
    }


    sp->rx += sp->vecteurx*5;
    sp->ry += sp->vecteury*5;

    sp->pos.x = sp->rx;
    sp->pos.y = sp->ry;

    /*
    sp->pos.x += sp->vecteurx*5;
    sp->pos.y += sp->vecteury*5;*/


    if((sp->pos.x>= ecran->w)
       || (sp->pos.y>= ecran->h)
       || (sp->pos.x<=0)
       || (sp->pos.y<=0))
    {
        sp->actif=0;
    }
}

//int clik=0;
SDL_Rect moneret;

int zo=0;
int za=0;

void tir_ennemi(struct balle_ennemi *sp, struct mur *spd, SDL_Rect pos, int R)
{
    int tx1,ty1,xv1,xy1;

    if(spd->actif==0){

    if(sp->clique==1)
    {
        sp->actif=1;

        sp->pos.x = spd->pos.x + R*cos((atan2(pos.x-spd->pos.x-30,spd->pos.y+30-pos.y))+29.8)+39+7;
        sp->pos.y = spd->pos.y + R*sin((atan2(pos.x-spd->pos.x-30,spd->pos.y+30-pos.y))+29.8)+39+7;


        sp->rx = sp->pos.x;
        sp->ry = sp->pos.y;


        tx1 = pos.x+30;
        ty1 = pos.y+30;

        xv1 = tx1 - sp->pos.x;
        xy1 = ty1 - sp->pos.y;

        longueur = sqrt(xv1*xv1 + xy1*xy1);

        sp->vecteurx =  (xv1/longueur);
        sp->vecteury = (xy1/longueur);



        /*
        if((spd->angle>270)&&(spd->angle<360)){

        spd->moneret.x=ecran->w;
        spd->moneret.y= ecran->h - abs ( spd->pos.y)  - abs( ((ecran->w - spd->pos.x)/(tan((360-spd->angle)*M_PI/180))) );

        }
        if((spd->angle>=0)&&(spd->angle<90)){

        spd->moneret.x=0;
        spd->moneret.y= ecran->h - abs ( spd->pos.y)  - abs( ((ecran->w - spd->pos.x)/(tan((360-spd->angle)*M_PI/180))) );

        }
        if((spd->angle>90)&&(spd->angle<180)){

        spd->moneret.x=0;
        spd->moneret.y=abs ( spd->pos.y)  + abs( ((ecran->w - spd->pos.x)/(tan((360-spd->angle)*M_PI/180))) );

        }
        if((spd->angle>180)&&(spd->angle<270)){

        spd->moneret.x=ecran->w;
        spd->moneret.y= abs ( spd->pos.y)  + abs( ((ecran->w - spd->pos.x)/(tan((360-spd->angle)*M_PI/180))) );

        }




        //sp->pos.x = spd->pos.x + R*cos((atan2(spd->moneret.x-spd->pos.x-30,spd->pos.y+30-spd->moneret.y))+29.8)+39+7;
        //sp->pos.y = spd->pos.y + R*sin((atan2(spd->moneret.x-spd->pos.x-30,spd->pos.y+30-spd->moneret.y))+29.8)+39+7;


        sp->rx = sp->pos.x;
        sp->ry = sp->pos.y;


        tx1 = spd->moneret.x;
        ty1 = spd->moneret.y;

        xv1 = tx1 - sp->pos.x;
        xy1 = ty1 - sp->pos.y;

        longueur = sqrt(xv1*xv1 + xy1*xy1);

        sp->vecteurx =  (xv1/longueur);
        sp->vecteury = (xy1/longueur);*/

        //sp->sprite = bullet[spd->angle];
        //sp->sprite = balleT;

        sp->clique=0;
    }

    sp->rx += sp->vecteurx*5;
    sp->ry += sp->vecteury*5;

    sp->pos.x = sp->rx;
    sp->pos.y = sp->ry;


    if((sp->pos.x>= ecran->w)
       || (sp->pos.y>= ecran->h)
       || (sp->pos.x<=0)
       || (sp->pos.y<=0))
    {
        sp->actif=0;
    }
    }
}

int tempo;

void impact_obstacle(struct tank *sp, struct obstacle *spd)
{
    if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
    {
        if((sp->pos.x + sp->sprite->w >=spd->pos.x)&&(sp->pos.x + sp->sprite->w<spd->pos.x+5))
        {
            sp->pos.x--;
        }
        if((sp->pos.y + sp->sprite->h >=spd->pos.y)&&(sp->pos.y + sp->sprite->h<spd->pos.y+5))
        {
            sp->pos.y--;
        }
        if((sp->pos.x <= spd->pos.x+ spd->sprite->w)&&(sp->pos.x > spd->pos.x-5 + spd->sprite->w))
        {
            sp->pos.x++;
        }
        if((sp->pos.y <= spd->pos.y + spd->sprite->h)&&(sp->pos.y > spd->pos.y + spd->sprite->h-5))
        {
            sp->pos.y++;
        }
    }
}

void impact_balle_mur(struct balle *sp, struct obstacle *spd)
{
    if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
    {
        sp->actif  = 0;
    }
}

void impact_balle_mur1(struct balle_ennemi *sp, struct obstacle *spd)
{
    if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
    {
        sp->actif  = 0;
    }
}

void impact_tank(struct tank *sp, struct  mur *spd)
{
    SDL_Rect posTerrainT;
    if(spd->actif==0){

    if(sp->touche==0)
    {
        if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
        {
            sp->hp=sp->hp-10;
            spd->hp--;
            sp->touche=1;
        if(spd->hp==0)
        {
            spd->explo=1;
            spd->actif = 1;
            spd->mort.x = spd->pos.x;
            spd->mort.y = spd->pos.y;

            //spd->pos.x = spd->pos.y = 2000;
        }
        }
    }
    }/*
    if(sp->touche==1)
    {
        tempo++;/*
        if(tempo%15==1)
        {
            clipper.x = sp->pos.x;
            clipper.y = sp->pos.y;

            clipper.h = sp->sprite->h;
            clipper.w = sp->sprite->w;

            SDL_SetClipRect(ecran, &clipper);

            posTerrainT.x = pos.x;
            posTerrainT.y = pos.y;

            SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);

            SDL_SetClipRect(ecran, NULL);
        }
        if(tempo>=350)
        {
            sp->touche=0;
            tempo=0;
        }
    }*/

}

void jsuistouche(struct tank *sp)
{
    if(sp->touche==1)
    {
        tempo++;/*
        if(tempo%15==1)
        {
            clipper.x = sp->pos.x;
            clipper.y = sp->pos.y;

            clipper.h = sp->sprite->h;
            clipper.w = sp->sprite->w;

            SDL_SetClipRect(ecran, &clipper);

            posTerrainT.x = pos.x;
            posTerrainT.y = pos.y;

            SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);

            SDL_SetClipRect(ecran, NULL);
        }*/
        if(tempo>=350)
        {
            sp->touche=0;
            tempo=0;
        }
    }
}

void fin_du_game(struct tank* sp)
{
    if(sp->hp<=0)
    {
        continuer=0;
    }
}

void impact_joueur(struct balle_ennemi* spd, struct tank* sp, struct mur* spdr)
{
    if(collision(sp->pos, spd->pos, sp->sprite, spd->sprite))
    {
        sp->hp--;
        spd->actif=0;

        if(eau==1)
        {
            spdr->hp--;
        }
    }
}


void detru_mur(struct mur* sp, struct balle* spd,struct tank* spdt)
{
    SDL_Rect posTerrainT;
    if(sp->actif==0){
    if(collision(sp->pos, spd->pos,sp->sprite, spd->sprite))
    {
        sp->hp--;
        spd->actif=0;

        if(feu==1)
        {
            if(sp->brulure3==1)
            {
                sp->brulure4=1;
            }
            if(sp->brulure2==1)
            {
                sp->brulure3=1;
            }
            if(sp->brulure1==1)
            {
                sp->brulure2=1;
            }
            if(sp->brulure==1)
            {
                sp->brulure1=1;
            }
            sp->brulure=1;
            //sp->pos.x -= sp->vecteurx*40;
            //sp->pos.y -= sp->vecteury*40;
        }

        if(eau==1)
        {
            sp->lent=1;
        }

        if(plante==1)
        {
            if(rand()%2==0)
            {
                sp->hp-=3;
            }
            spdt->hp++;
        }
        /*
        if(sp->hp<=0)
        {
            sp->explo=1;

            sp->mort.x = sp->pos.x;
            sp->mort.y = sp->pos.y;
            //sp->pos.x = sp->pos.y = 2000;
            sp->actif = 1;
            ennemi--;
        }*/

    }

    }
}

void Test_mort(struct mur* sp)
{
        if(sp->hp<=0)
        {
            sp->explo=1;

            sp->mort.x = sp->pos.x;
            sp->mort.y = sp->pos.y;
            //sp->pos.x = sp->pos.y = 2000;
            sp->actif = 1;
            ennemi--;
        }
}

void ralentissement(struct mur* sp)
{
    if(sp->lent==1)
    {

    sp->ralentit++;

    if(sp->ralentit>=300)
    {
        sp->ralentit=0;
        sp->lent=0;
    }

    }

}

void bruler(struct mur* sp)
{
    if(sp->brulure==1)
    {
        sp->Temps_brulure++;

        if(sp->Temps_brulure%40==20)
        {
            sp->hp--;
            if(sp->brulure1==1)
            {
                sp->hp--;
            }
            if(sp->brulure2==1)
            {
                sp->hp--;
            }
            if(sp->brulure3==1)
            {
                sp->hp--;
            }
            if(sp->brulure4==1)
            {
                sp->hp--;
            }
        }

        if(sp->Temps_brulure>=300)
        {
            sp->Temps_brulure=0;
            sp->brulure=0;
            sp->brulure1=0;
            sp->brulure2=0;
            sp->brulure3=0;
            sp->brulure4=0;
        }
    }

  /*  if(sp->hp<=0)
    {
        sp->explo=1;

        sp->mort.x = sp->pos.x;
        sp->mort.y = sp->pos.y;
            //sp->pos.x = sp->pos.y = 2000;
        sp->actif = 1;
        ennemi--;
    }*/
}

void Test_tir(struct balle *sp)
{
    if(sp->impact==1)
    {
        sp->tempo_impact++;

        if(sp->tempo_impact>=9)
        {
            sp->tempo_impact=0;
            sp->frame_impact++;
        }

        if(sp->frame_impact>=7)
        {
            sp->impact=0;
            sp->frame_impact=0;
        }
    }
}


void boom(struct mur* sp)
{
    //SDL_Rect posTerrainT;

    if(sp->explo==1)
    {
        sp->frame++;
        if(sp->frame>=81)
        {
            sp->explo=0;
        }
/*
        clipper.x = sp->mort.x;
        clipper.y = sp->mort.y;

        clipper.h = 100;
        clipper.w = 100;

        SDL_SetClipRect(ecran, &clipper);

        posTerrainT.x = pos.x;
        posTerrainT.y = pos.y;

        SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);

        SDL_SetClipRect(ecran, NULL);

        SDL_BlitSurface(explosion, &clipe[sp->frame], ecran, &sp->mort);*/
    }
}

int lance_feu=0;

void quit()
{
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    continuer=0;
                    fin=0;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            droite=1;
                            //gauche=haut=bas=0;
                            break;
                        case SDLK_LEFT:
                            gauche=1;
                            //droite=haut=bas=0;
                            break;
                        case SDLK_UP:
                            haut=1;
                            //droite=gauche=bas=0;
                            break;
                        case SDLK_DOWN:
                            bas=1;
                            //droite=gauche=haut=0;
                            break;
                        case SDLK_SPACE:
                            if(fin)
                            {
                                fin=0;
                            }
                          break;
                        case SDLK_ESCAPE:
                            continuer=0;
                            fin=0;
                            break;
                        default:
                            break;
                    }
                     break;

                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            droite=0;
                            break;
                        case SDLK_LEFT:
                            gauche=0;
                            break;
                        case SDLK_UP:
                            haut=0;
                            break;
                        case SDLK_DOWN:
                            bas=0;
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    mvtx = event.motion.x;
                    mvty = event.motion.y;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            if(choixTank)
                            {
                                if(event.button.y<184)
                                {
                                    feu=1;
                                }
                                if((event.button.y>=184)
                                   &&(event.button.y<368))
                                {
                                    eau=1;
                                }
                                if(event.button.y>=368)
                                {
                                    plante=1;
                                }
                                choixTank=0;
                            }
                            else{
                              for(int i=0;i<50;i++)
                            {
                                if(tir[i].actif==0)
                                {
                                    tir[i].actif=1;
                                    tir[i].clique=1;
                                    break;
                                }
                            }
                            }

                            break;
                        case SDL_BUTTON_RIGHT:
                            if(feu==1)
                            {
                                lance_feu=1;
                            }

                            break;
                        default:
                            break;

                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_RIGHT:
                            lance_feu=0;
                            break;
                        default:
                            break;

                    }
                    break;
            }
        }

}

void clip_hp(SDL_Rect OLD, SDL_Surface *terrain)
{
    SDL_Rect posTerrainT;

    clipper.h = 8;
    clipper.w = 69;

    clipper.x = OLD.x+10;
    clipper.y = OLD.y-12;

    SDL_SetClipRect(ecran, &clipper);

    posTerrainT.x = pos.x;
    posTerrainT.y = pos.y;

    SDL_BlitSurface(terrain, NULL, ecran, &posTerrainT);
}

int t=0;
int t2=0;

void hp(struct mur *sp, SDL_Rect R)
{
    SDL_Rect B, B1, B2, B3, B4;
    SDL_Rect A;

    B.x = R.x+10;
    B.y = R.y-12;
    B.w = 69;
    B.h = 8;

    A.x = R.x+10;
    A.y = R.y-12;
    A.w = sp->hp * 1.38;
    A.h = 8;

    SDL_FillRect(ecran, &B, SDL_MapRGB(ecran->format, 128,0,0));
    SDL_FillRect(ecran, &A, SDL_MapRGB(ecran->format, 0,128,0));

    B.x = 5+R.x+10;
    B.y = R.y-12;
    B.w = 69;
    B.h = 8;

    if(sp->brulure==1)
    {
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B);
    }

    B1.x = 5+R.x+10+10;
    B1.y = R.y-12;
    B1.w = 69;
    B1.h = 8;

    if(sp->brulure1==1)
    {
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B1);
    }

    B2.x = 5+R.x+10+10+10;
    B2.y = R.y-12;
    B2.w = 69;
    B2.h = 8;

    if(sp->brulure2==1)
    {
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B1);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B2);
    }

    B3.x = 5+R.x+10+10+10+10;
    B3.y = R.y-12;
    B3.w = 69;
    B3.h = 8;

    if(sp->brulure3==1)
    {
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B1);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B2);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B3);
    }

    B4.x = 5+R.x+10+10+10+10+10;
    B4.y = R.y-12;
    B4.w = 69;
    B4.h = 8;

    if(sp->brulure4==1)
    {
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B1);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B2);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B3);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &B4);
    }
}

void hp_joueur(struct tank *sp)
{
    SDL_Rect A, B;

    B.x = hp_pos.x+ 50 ;
    B.y = hp_pos.y +30;
    B.h = 25;
    B.w = 260;

    A.x =hp_pos.x+ 50;
    A.y =hp_pos.y +30;
    A.w = sp->hp * 0.26;
    A.h = 25;

    SDL_FillRect(ecran, &B, SDL_MapRGB(ecran->format, 128,0,0));
    SDL_FillRect(ecran, &A, SDL_MapRGB(ecran->format, 0,128,0));
}

void Set_General_Clip(int ligne, int colonne, int taille)
{
    SDL_Rect Gclip[ligne*colonne];

    for(int i = 0; i<ligne; i++)
    {
        for(int j=0; j<colonne; j++)
        {
            Gclip[i+ligne*j].x = i*taille;
            Gclip[i+ligne*j].y = j*taille;
            Gclip[i+ligne*j].w = taille;
            Gclip[i+ligne*j].h = taille;
        }
    }
}

void Set_Clip()
{
    for(int i = 0;i<9;i++)
    {
        for(int j = 0;j<9;j++)
        {
            clipe[i+9*j].x = i*100;
            clipe[i+9*j].y = j*100;
            clipe[i+9*j].w = 100;
            clipe[i+9*j].h = 100;
        }
    }
}

void Set_Clip1()
{
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<2;j++)
        {
            clipe1[i+3*j].x = i*20;
            clipe1[i+3*j].y = j*20;
            clipe1[i+3*j].w = 20;
            clipe1[i+3*j].h = 20;
        }
    }
}

void Set_Clip2()
{
    for(int i = 0;i<6;i++)
    {
        clipe2[i].x = i*45;
        clipe2[i].y = 0;
        clipe2[i].w = 45;
        clipe2[i].h = 45;
    }
}

void Set_Clip3()
{
    for(int i = 0;i<10;i++)
    {
        clipe3[i].x = i*20;
        clipe3[i].y = 0;
        clipe3[i].w = 20;
        clipe3[i].h = 20;
    }
}

int temps;
int slow;

int tps=0;
int tps2=0;

int main ( int argc, char** argv )
{
    init();


    while(choixTank)
    {
        quit();
        SDL_BlitSurface(choix, NULL, ecran, &pos);
        SDL_Flip(ecran);
    }

    SDL_BlitSurface(terrain, NULL, ecran, &pos);

        if(feu==1)
        {
            corps = IMG_Load("corpsE111.png");
            arme = IMG_Load("armeE111.png");
            animeau = IMG_Load("anifeu.png");
        }
        if(eau==1)
        {
            corps = IMG_Load("corps111.png");
            arme = IMG_Load("arme11.png");
            animeau = IMG_Load("animeau.png");
        }
        if(plante==1)
        {
            corps = IMG_Load("corpsV111.png");
            arme = IMG_Load("armeV111.png");
            animeau = IMG_Load("aniplante.png");
        }
        corpsT = rotozoomSurface(corps,0,1,1);
        armeT =  rotozoomSurface(arme,0,0.3,1);

     /*   if(plante==1)
        {
        for(int i=0;i<360;i++)
        {
            test[i] = rotozoomSurface(arme,i,0.3,1);
        }

        for(int i=0;i<4;i++)
        {
            test1[i] = rotozoomSurface(corps,i*90,0.3,1);
        }
        }
        else{*/
        for(int i=0;i<360;i++)
        {
            test[i] = rotozoomSurface(arme,i,1,1);
        }

        for(int i=0;i<4;i++)
        {
            test1[i] = rotozoomSurface(corps,i*90,1,1);
        }
        //}
        test1[4] = rotozoomSurface(corps,225,0.3,1);

    struct tank arm;
    struct tank cor;



    srand(time(NULL));

    init_joueur(&cor);

    /*
    for(int i=0;i<3;i++)
    {
        init_obstacle(&caillou[i], 200+i*200, ecran->h/2 - 50);
    }*/

    init_obstacle(&caillou[0], 200, ecran->h/2 - 69);
    init_obstacle(&caillou[1], 450, ecran->h/2 - 152);
    init_obstacle(&caillou[2], 750, ecran->h/2 + 100);
    init_obstacle(&caillou[3], 450, ecran->h/2 + 50);


    for(int i = 0; i<50;i++)
    {
        init_tir(&tir[i]);
        for(int j=0;j<nb_ennemi;j++){
        init_tir_ennemi(&tire[i][j]);
        }
    }

    for(int i=0;i<nb_ennemi;i++)
    {
        init_mur(&pierre[i]);
        pierre[i].pos.x = 1000;
        pierre[i].pos.y = i*100;
    }

    Set_Clip();
    Set_Clip1();
    Set_Clip2();
    Set_Clip3();

    SDL_Rect ludwig;



    while(continuer)
    {
        quit();

        if(eau==1){
        for(int i = 0;i<nb_ennemi;i++)
        {
            ralentissement(&pierre[i]);
        }}

        if(feu==1){
        for(int i = 0;i<nb_ennemi;i++)
        {
            bruler(&pierre[i]);
        }}

        if(ennemi==0)
        {
            continuer =0;
        }

        fin_du_game(&cor);

        for(int i =0;i<nb_ennemi;i++)
        {
          add_tank(&pierre[i]);
        }

        deplaJ(&cor);

        for(int i =0;i<4;i++)
        {
            impact_obstacle(&cor, &caillou[i]);
        }



        temps++;
        //zbeub++;

        if(temps>=80)
        {
            temps=0;
        }

        slow = temps%3;

        //if(temps==40){
        for(int j=0;j<nb_ennemi;j++){
            if(temps == pierre[j].tps_tir){
            for(int i=0;i<50;i++)
                    {
                        if(tire[i][j].actif==0)
                        {
                            tire[i][j].actif=1;
                            tire[i][j].clique=1;
                            break;
                        }
                    }
            }
        }
        //}

        for(int i = 0; i<nb_ennemi;i++)
        {

            if(pierre[i].actif==0)
            {
               // if(slow==0)
               //{
                    if(pierre[i].ralentit%5 == 0)
                    {
                    depla_suit(&pierre[i], &cor);
                    for(int j=0;j<4;j++){
                    ennemi_mur(&pierre[i],&caillou[j], &cor);
                    for(int r=0;r<nb_ennemi;r++)
                    {
                        if(r!=i)
                        {
                            ennemi_ennemi(&pierre[i], &pierre[r], &cor);
                        }
                    }
                    }
                    }
               // }

            }
        }

        for(int i=0;i<50;i++)
        {
                if(tir[i].actif==1)
                {
                    tir_joueur(&tir[i], cor.pos, 40);
                }
                for(int j=0;j<nb_ennemi;j++){
                if(tire[i][j].actif==1)
                {
                    tir_ennemi(&tire[i][j], &pierre[j], cor.pos, 40);
                }
                }

        }

        for(int i=0;i<50;i++)
        {
            for(int j=0;j<4;j++)
            {
                impact_balle_mur(&tir[i], &caillou[j]);
            }
        }

        for(int k=0;k<nb_ennemi;k++){
        for(int i=0;i<50;i++)
        {
            for(int j=0;j<4;j++)
            {
                impact_balle_mur1(&tire[i][k], &caillou[j]);
            }
        }
        }

        clip(cor.oldpos, terrain, cor.sprite);
        clip(cor.oldpos2, terrain, cor.sprite2);

        for(int i = 0; i<nb_ennemi;i++)
        {
            clip(pierre[i].oldpos, terrain,  pierre[i].sprite);
            clip(pierre[i].oldpos2, terrain, pierre[i].sprite2);
            clip_hp(pierre[i].oldpos, terrain);
        }

        for(int i=0;i<50;i++)
        {
            clip_anim(tir[i].oldpos, terrain, 20,20);
            //clip(tir[i].pos_impact, terrain, fume_anim[tir[i].frame_impact][tir[i].angle] );
            for(int j=0;j<nb_ennemi;j++){
            clip(tire[i][j].oldpos, terrain, tire[i][j].sprite);
            }
        }

        for(int i=0;i<nb_ennemi;i++)
        {
            if(pierre[i].explo==1)
            {
                clip_anim(pierre[i].mort, terrain, 100,100);
            }
        }

        if(feu==1)
        {
            clip1(ludwig, terrain, FTA[tps2][cor.angle] );
        }



        for(int i = 0; i<nb_ennemi;i++)
        {
            boom(&pierre[i]);
        }


        t++;
        if(t>=6)
        {
            t=0;
            t2++;

            if(t2>=5)
            {
                t2=0;
            }
        }

        for(int i=0;i<50;i++)
        {
            if(tir[i].actif==1)
            {
                //affiche(tir[i].pos,tir[i].sprite);
                affiche_anim(tir[i].pos, animeau, &clipe1[0], t2);
            }

            for(int j=0;j<nb_ennemi;j++){
            if(tire[i][j].actif==1)
            {
                if(pierre[j].actif==0){
                    affiche(tire[i][j].pos,tire[i][j].sprite);
                }
            }
            }
        }


        if(tempo%6!=1)
        {
            affiche(cor.pos,cor.sprite);
            affiche(cor.pos2,cor.sprite2);
        }

        for(int i = 0; i<nb_ennemi;i++)
        {
            if(pierre[i].actif==0)
            {
                affiche(pierre[i].pos, pierre[i].sprite);
                affiche(pierre[i].pos2, pierre[i].sprite2);
            }
        }

        for(int i=0;i<4;i++)
        {
            affiche(caillou[i].pos, caillou[i].sprite);
        }

        for(int i=0;i<nb_ennemi;i++)
        {

            if(pierre[i].explo==1)
            {
                 affiche_anim(pierre[i].mort, explosion, &clipe[0], pierre[i].frame);
            }

        }

      /*  for(int i=0;i<50;i++)
        {
            if(tir[i].actif==1)
            {
                //affiche(tir[i].pos,tir[i].sprite);
                affiche_anim(tir[i].pos, animeau, &clipe1[0], t2);
            }

            for(int j=0;j<nb_ennemi;j++){
            if(tire[i][j].actif==1)
            {
                if(pierre[j].actif==0){
                    affiche(tire[i][j].pos,tire[i][j].sprite);
                }
            }
            }
        }
*/



        /*for(int i = 0;i<50;i++)
        {
            Test_tir(&tir[i]);
            if(tir[i].impact==1)
            {
                affiche(tir[i].pos_impact, fume_anim[tir[i].frame_impact][tir[i].angle]);
            }
        }*/

        cor.oldpos.x = cor.pos.x;
        cor.oldpos.y = cor.pos.y;

        cor.oldpos2.x = cor.pos2.x;
        cor.oldpos2.y = cor.pos2.y;

        for(int i = 0; i<nb_ennemi;i++)
        {
            pierre[i].oldpos.x = pierre[i].pos.x;
            pierre[i].oldpos.y = pierre[i].pos.y;

            pierre[i].oldpos2.x = pierre[i].pos2.x;
            pierre[i].oldpos2.y = pierre[i].pos2.y;
        }

        for(int i=0;i<50;i++)
        {
            tir[i].oldpos.x = tir[i].pos.x;
            tir[i].oldpos.y = tir[i].pos.y;

            for(int j=0;j<nb_ennemi;j++){
            tire[i][j].oldpos.x = tire[i][j].pos.x;
            tire[i][j].oldpos.y = tire[i][j].pos.y;
            }

        }

        for(int i=0;i<50;i++)
        {
            for(int j=0; j<nb_ennemi;j++)
            {
                if(tir[i].actif==1)
                {
                    detru_mur(&pierre[j], &tir[i], &cor);
                }
            }
        }

        for(int i = 0;i<nb_ennemi;i++)
        {
            Test_mort(&pierre[i]);
        }

        for(int i=0;i<50;i++)
        {
            for(int j=0; j<nb_ennemi;j++)
            {
                if(tire[i][j].actif==1)
                {
                    if(cor.touche ==0){
                            if(pierre[j].actif==0){
                                impact_joueur(&tire[i][j], &cor, &pierre[j]);
                            }
                    }
                }
            }
        }

        for(int i=0;i<nb_ennemi;i++)
        {
            impact_tank(&cor, &pierre[i]);
        }

        jsuistouche(&cor);

        sprintf(write, "hp : %d, ennemi : %d, %d, %d, %d ", cor.hp, ennemi,ecran->w, cor.pos.x, pierre[0].moneret.y);
        texte = TTF_RenderText_Solid(police, write, NOIRE);
        SDL_FillRect(ecran, &posT, SDL_MapRGB(ecran->format, 255,255,255));

        SDL_BlitSurface(texte, NULL, ecran, &pos);

        tps++;

        if(tps>=7)
        {
            tps2++;
            tps=0;

            if(tps2>=7)
            {
                tps2=0;
            }
        }



        ludwig.x = cor.pos.x+46 - FTA[tps2][cor.angle]->w / 2 + 150*cos((atan2(mvtx-cor.pos.x-30-20,cor.pos.y+30+20-mvty))+29.8);
        ludwig.y = cor.pos.y+46 - FTA[tps2][cor.angle]->h / 2 + 150*sin((atan2(mvtx-cor.pos.x-30-20,cor.pos.y+30+20-mvty))+29.8);

        if(lance_feu==1)
        {
            SDL_BlitSurface(FTA[tps2][cor.angle], NULL, ecran, &ludwig);

            for(int i=0;i<nb_ennemi;i++)
            {

                if(collision(pierre[i].pos, ludwig,pierre[i].sprite, FTA[tps2][cor.angle]))
                {
                    //pierre[i].hp--;

                    if(feu==1)
                    {
                        if(pierre[i].brulure3==1)
                        {
                            pierre[i].brulure4=1;
                        }
                        if(pierre[i].brulure2==1)
                        {
                            pierre[i].brulure3=1;
                        }
                        if(pierre[i].brulure1==1)
                        {
                            pierre[i].brulure2=1;
                        }
                        if(pierre[i].brulure==1)
                        {
                            pierre[i].brulure1=1;
                        }
                        pierre[i].brulure=1;
                        //sp->pos.x -= sp->vecteurx*40;
                        //sp->pos.y -= sp->vecteury*40;
                    }

                }
            }
        }

        /*SDL_Rect ludwig, ludwig1, ludwig2, ludwig3, ludwig4;

        ludwig.x = cor.pos.x +10+5;
        ludwig.y = cor.pos.y -25;

        ludwig1.x = cor.pos.x+10 +10+5;
        ludwig1.y = cor.pos.y -25;

        ludwig2.x = cor.pos.x +20+10+5;
        ludwig2.y = cor.pos.y -25;

        ludwig3.x = cor.pos.x+30 +10+5;
        ludwig3.y = cor.pos.y -25;

        ludwig4.x = cor.pos.x+40 +10+5;
        ludwig4.y = cor.pos.y -25;

        SDL_BlitSurface(brule, &clipe3[t2], ecran, &ludwig);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &ludwig1);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &ludwig2);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &ludwig3);
        SDL_BlitSurface(brule, &clipe3[t2], ecran, &ludwig4);*/
        //SDL_BlitSurface(fume_anim[tps2][0], NULL, ecran, &ludwig);

        hp_joueur(&cor);

        for(int i = 0; i<nb_ennemi;i++)
        {
            if(pierre[i].actif==0)
            {
                hp(&pierre[i],pierre[i].pos);
            }
        }

        SDL_BlitSurface(barreT, NULL, ecran, &hp_pos);


        SDL_Flip(ecran);

        SDL_Delay(6);
        zbeub++;
    }

    while(fin)
    {
        SDL_Rect w;

        w.x = 280;
        w.y = 200;

        quit();
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));

        if(cor.hp<=0)
        {
            SDL_BlitSurface(wasted,NULL,ecran, &w);
        }

        if(ennemi<=0)
        {
            SDL_BlitSurface(victoire,NULL,ecran, &w);
        }

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(corps);
    SDL_FreeSurface(corpsT);
    SDL_FreeSurface(arme);
    SDL_FreeSurface(armeT);
    SDL_FreeSurface(balle);
    SDL_FreeSurface(balleT);
    SDL_FreeSurface(terrain);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(murT);
    SDL_FreeSurface(mure);
    SDL_FreeSurface(mureT);
    SDL_FreeSurface(explosion);

    SDL_Quit();
    return EXIT_SUCCESS;
}
