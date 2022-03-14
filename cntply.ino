void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
   char a[1000];
   char ch;
   int co, l, i;
   float fq, du;
   boolean sh=false, oc=false, cmt=false;
   co=4;
   l=0;
   while (Serial.readBytes(&ch,1) > 0) {
      a[l]=ch;
      if (a[l]=='\'') cmt=true;
      if (a[l]!='\n' && cmt==false) l++;
      if (a[l]=='\n') cmt=false; 
   }
   if (l>0) {
     i=0;
     do {
       //a[i]=fgetc(fp);
       //a[i+1]=fgetc(fp);
       //cout << ch[0];
       fq=0;
       du=0;
       a[i]=tolower(a[i]);
       if (a[i]=='#')
       {
          sh=true;
       }
       if (a[i]=='c')
         if (sh) fq=138.59; else fq=130.81;
       if (a[i]=='d')
         if (sh) fq=155.56; else fq=146.83;
       if (a[i]=='e') fq=164.81;
       if (a[i]=='f')
         if (sh) fq=185.00; else fq=174.61;
       if (a[i]=='g')
         if (sh) fq=207.65; else fq=196.00;
       if (a[i]=='a')
         if (sh) fq=233.08; else fq=220.00;
       if (a[i]=='b') fq=246.94;
       if (a[i]!='*')
         if (a[i+1]=='0') du=1; else du=1/pow(2,(a[i+1]-'0'));
       else co=a[i+1]-'0';
       if (a[i]>='a' && a[i]<='g') sh=false;
       if ((a[i+1]<'0' || a[i+1]>'9') && a[i]!='#')
       {
         oc=true;
         du=0.125;
       }
       tone(8, fq*(pow(2,co)/2));
       delay(2000*du);
       noTone(8);
       if (sh || oc)
       {
         oc=false;
         i++;
       } else i=i+2;
     } while (i<(l-1));
   }
}
