#include <iostream>
#include <string.h> //cstrings's header file is string.h (https://www.cplusplus.com/reference/cstring) 
#include <fstream>
using namespace std;
const int M=100;
const int L=500;
struct CAR{
  char CARNAME[M];
  double MPG;
  int CYLINDERS;
  double DISPLACEMENT;
  double HORSEPOWER;
  double WEIGHT;
  double ACCELERATION;
  int MODEL;
  char ORIGIN[M];
  bool VALIDENTRY;
  bool S;
  CAR();
};
CAR::CAR(){
  strcpy(CARNAME,"NULL");
  MPG=0.0;
  CYLINDERS=0;
  DISPLACEMENT=0.0;
  HORSEPOWER=0.0;
  WEIGHT=0.0;
  ACCELERATION=0.0;
  MODEL=0;
  strcpy(ORIGIN,"NULL");
  VALIDENTRY=0;
  S=0;
}
CAR FILELOADER(ifstream &INP){
  CAR WORK;
  INP.get(WORK.CARNAME,M,';');
  INP.ignore(M,';');
  INP>>WORK.MPG;
  INP.ignore(M,';');
  INP>>WORK.CYLINDERS;
  INP.ignore(M,';');
  INP>>WORK.DISPLACEMENT;
  INP.ignore(M,';');
  INP>>WORK.HORSEPOWER;
  INP.ignore(M,';');
  INP>>WORK.WEIGHT;
  INP.ignore(M,';');
  INP>>WORK.ACCELERATION;
  INP.ignore(M,';');
  INP>>WORK.MODEL;
  INP.ignore(M,';');
  INP.get(WORK.ORIGIN,M,'\n');
  INP.ignore(M,'\n');
  WORK.VALIDENTRY=!INP.eof();
  WORK.S=true;
  return WORK;
}
int READCARSFILE(CAR (&ALLCARS)[L]){
  clog<<"LOADING CARS FILE...";
  try{
    int INDEX=0;
    ifstream INPUTFILE("./cars.txt");
    while(INPUTFILE.peek()!=EOF&&INDEX<L){
      ALLCARS[INDEX]=FILELOADER(INPUTFILE);
      INDEX++;
    }
    clog<<"\e[1;32mDONE! ("<<INDEX<<" entries)\e[0m\n";
    return INDEX;
  }catch(...){
    cerr<<"\e[1;31mFAILED!\nACCESS DENIED OR FILE DOES NOT EXIST!\n\e[0m;";
    return 0;
  }
}
int VERIFYCAR(CAR INPUT){
  if(!INPUT.VALIDENTRY){
    return 1;
  }else if(INPUT.CARNAME=="NULL"){
    return 2;
  }else if(INPUT.ORIGIN=="NULL"){
    return 3;
  }
  return 0;
}
void PRINTCARS(int NUMCARS,CAR ALLCARS[L]){
  int IDEX=0;
  while(IDEX<=NUMCARS){
    int C=VERIFYCAR(ALLCARS[IDEX]);
    if(C){
      cerr<<"\e[1;3;33mINDEX "<<IDEX<<":\tINVALID (\e[4m";
      switch(C){
        case 1:
          cerr<<"NOT A VALID ENTRY!";
          break;
        case 2:
          cerr<<"NO NAME!";
          break;
        case 3:
          cerr<<"NO ORIGIN!";
      }
      cerr<<"\e[0;1;3;33m), SKIPPING...\e[0m\n";
      IDEX++;
      continue;
    }
    cout<<"INDEX "<<IDEX<<":\t\e[1;36m"<<ALLCARS[IDEX].CARNAME<<"\e[0m;"<<ALLCARS[IDEX].MPG<<";"<<ALLCARS[IDEX].CYLINDERS<<";"<<ALLCARS[IDEX].DISPLACEMENT<<";"<<ALLCARS[IDEX].HORSEPOWER<<";"<<ALLCARS[IDEX].WEIGHT<<";"<<ALLCARS[IDEX].ACCELERATION<<";"<<ALLCARS[IDEX].MODEL<<";\e[1;36m"<<ALLCARS[IDEX].ORIGIN<<"\e[0m\t\t\t(Source: \e[1m";
    if(ALLCARS[IDEX].S){
      cout<<"\e[32mFile\e[0m)\n";
    }else{
      cout<<"\e[36mUser Input\e[0m)\n";
    }
    IDEX++;
  }
}
void PRINTCARSBYORIGIN(int NUMCARS,CAR ALLCARS[L],char* ORIGIN){
  int IDEX=0;
  while(IDEX<=NUMCARS){
    int C=VERIFYCAR(ALLCARS[IDEX]);
    if(strcmp(ALLCARS[IDEX].ORIGIN,ORIGIN)){
      clog<<"\e[1;3;33mINDEX "<<IDEX<<":\tNOT FROM "<<ORIGIN<<", SKIPPING...\e[0m\n";
      IDEX++;
      continue;
    }
    if(C){
      cerr<<"\e[1;3;33mINDEX "<<IDEX<<":\tINVALID (\e[4m";
      switch(C){
        case 1:
          cerr<<"NOT A VALID ENTRY!";
          break;
        case 2:
          cerr<<"NO NAME!";
          break;
        case 3:
          cerr<<"NO ORIGIN!";
      }
      cerr<<"\e[0;1;3;33m), SKIPPING...\e[0m\n";
      IDEX++;
      continue;
    }
    cout<<"INDEX "<<IDEX<<":\t\e[1;36m"<<ALLCARS[IDEX].CARNAME<<"\e[0m;"<<ALLCARS[IDEX].MPG<<";"<<ALLCARS[IDEX].CYLINDERS<<";"<<ALLCARS[IDEX].DISPLACEMENT<<";"<<ALLCARS[IDEX].HORSEPOWER<<";"<<ALLCARS[IDEX].WEIGHT<<";"<<ALLCARS[IDEX].ACCELERATION<<";"<<ALLCARS[IDEX].MODEL<<";\e[1;36m"<<ALLCARS[IDEX].ORIGIN<<"\e[0m\t\t\t(Source: \e[1m";
    if(ALLCARS[IDEX].S){
      cout<<"\e[32mFile\e[0m)\n";
    }else{
      cout<<"\e[36mUser Input\e[0m)\n";
    }
    IDEX++;
  }
}
int REMOVECAR(int NUMCARS,CAR (&ALLCARS)[L],int ENTRYNUM){
  cout<<"REMOVING INDEX "<<ENTRYNUM<<"...";
  try{
    if(ENTRYNUM>=NUMCARS||ENTRYNUM>=L){throw 1;}
    for(int I=ENTRYNUM;I<NUMCARS;I++){
      ALLCARS[I]=ALLCARS[I+1];
    }
    cout<<"\e[1;32mDONE!\e[0m\n";
    return NUMCARS-1;
  }catch(...){
    cerr<<"\e[1;31mFAILED!\n\tOUT-OF-BOUNDS OR EMPTY LIST!\e[0m\n";
    return NUMCARS;
  }
}
int ADDCAR(int NUMCARS,CAR (&ALLCARS)[L],string A,double B,int C,double D,double E,double F,double G,int H,string I,bool J){
  // Uses same syntax as cars.txt
  cout<<"ADDING \""<<A<<"\"...";
  CAR T;
  for(int IND=0;IND<A.length();IND++){
    T.CARNAME[IND]=A[IND];
  }
  T.CARNAME[A.length()]='\0';
  T.MPG=B;
  T.CYLINDERS=C;
  T.DISPLACEMENT=D;
  T.HORSEPOWER=E;
  T.WEIGHT=F;
  T.ACCELERATION=G;
  T.MODEL=H;
  for(int IND=0;IND<I.length();IND++){
    T.ORIGIN[IND]=I[IND];
  }
  T.ORIGIN[I.length()]='\0';
  T.VALIDENTRY=J;
  T.S=false;
  // T.VALIDENTRY=VERIFYCAR(T);
  int INDEX=0;
  for(INDEX=0;ALLCARS[INDEX].VALIDENTRY;INDEX++){
    //
  }
  ALLCARS[INDEX]=T;
  cout<<"\e[1;32mDONE!\e[0m\t(INDEX "<<INDEX<<")\n";
  return NUMCARS++;
}
void MENUTASK(int &NUMCARS,CAR (&ALLCARS)[L]){
  bool KG=1;
  while(KG){
    cout<<"\e[0m\n"; //resets xterm
    cout<<"CARS DB APP\n\n\tMENU:\n\t\t1)\tPrint cars\n\t\t2)\tRemove car\n\t\t3)\tAdd car\n\t\t4)\tPrint cars by origin\n\t\t5)\tExit\nINPUT:";
    int INPUT=0;
    int INPUT2_0=0;
    char INPUT3_0[M]={'N','U','L','L','\0'};
    double INPUT3_1=0.0;
    int INPUT3_2=0;
    double INPUT3_3=0.0;
    double INPUT3_4=0.0;
    double INPUT3_5=0.0;
    double INPUT3_6=0.0;
    int INPUT3_7=0;
    char INPUT3_8[M]={'N','U','L','L','\0'};
    bool INPUT3_9=false;
    char INPUT4_0[M]={'\0'};
    cin>>INPUT;
    switch(INPUT){
      case 1:
        PRINTCARS(NUMCARS,ALLCARS);
        break;
      case 2:
        cout<<"REMOVE WHICH INDEX:";
        cin>>INPUT2_0;
        NUMCARS=REMOVECAR(NUMCARS,ALLCARS,INPUT2_0);
        break;
      case 3:
        cout<<"CARNAME:";
        cin>>INPUT3_0;
        cout<<"MPG:";
        cin>>INPUT3_1;
        cout<<"CYLINDERS:";
        cin>>INPUT3_2;
        cout<<"DISPLACEMENT:";
        cin>>INPUT3_3;
        cout<<"HORSEPOWER:";
        cin>>INPUT3_4;
        cout<<"WEIGHT:";
        cin>>INPUT3_5;
        cout<<"ACCELERATION:";
        cin>>INPUT3_6;
        cout<<"MODEL:";
        cin>>INPUT3_7;
        cout<<"ORIGIN:";
        cin>>INPUT3_8;
        cout<<"VALIDENTRY:";
        cin>>INPUT3_9;
        NUMCARS=ADDCAR(NUMCARS,ALLCARS,INPUT3_0,INPUT3_1,INPUT3_2,INPUT3_3,INPUT3_4,INPUT3_5,INPUT3_6,INPUT3_7,INPUT3_8,INPUT3_9);
        break;
      case 4:
        cout<<"ORIGIN:";
        cin>>INPUT4_0;
        PRINTCARSBYORIGIN(NUMCARS,ALLCARS,INPUT4_0);
        break;
      default:
        KG=0;
    }
  }
  cout<<"GOODBYE";
}
int main(){
  // char U[3]={'U','S','\0'};
  CAR ALLCARS[L];
  int NUMCARS=READCARSFILE(ALLCARS);
  MENUTASK(NUMCARS,ALLCARS);
  return 76;
  // PRINTCARS(NUMCARS,ALLCARS);
  // PRINTCARSBYORIGIN(NUMCARS,ALLCARS,U);
  // NUMCARS=REMOVECAR(NUMCARS,ALLCARS,69);
  // PRINTCARS(NUMCARS,ALLCARS);
  // NUMCARS=ADDCAR(NUMCARS,ALLCARS,"UR MOM",1.0,33,5.5,3.4,6.9,7.6,34,"US",1);
  // PRINTCARS(NUMCARS,ALLCARS);
}