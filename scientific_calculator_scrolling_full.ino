      #include<Keypad.h>
      #include<LiquidCrystal_I2C.h>
      LiquidCrystal_I2C sujaylcd(0x27,16,2);
      const byte row =4;
      const byte col = 4;
      char key[row][col]= {
        {'1','2','3','D'}, // at last of this row there is null "\0" character automatically assigned to tell computer that its the end of this row.
        {'4','5','6','*'},
        {'7','8','9','C'},
        {'#','0','A','B'}
      };
      char key1[row][col]= {
              {'s','c','t','A'}, // at last of this row there is null "\0" character automatically assigned to tell computer that its the end of this row.
              {'q','b','T','('},
              {'l','^','o',')'},
              {'m','e','n','r'}
              };
      byte rowpin[row]={9,8,7,6};
      byte colpin[col]={5,4,3,2};
      
      int angle=0,i=0,ans=0,k=0,s=0,j,l,b=0;
      float answer,num[10];
      int inv_angle;
      double sina;
      double cosa;
      double tana;
      float asina,acosa,atana,expa,loga,root;
      double pi = 3.1415926535 ;
      int sinp=10, cosp=11, tanp=12, logp=13;
      char val,action[10];
      String que;
      Keypad keysujay = Keypad(makeKeymap(key), rowpin , colpin , row , col);
      Keypad keysujay1 = Keypad(makeKeymap(key1), rowpin , colpin , row , col);
      
      void setup() {
        Serial.begin(9600);
        sujaylcd.clear();
        sujaylcd.init();
        sujaylcd.backlight();
        pinMode(sinp, INPUT);
        pinMode(cosp, INPUT);
        pinMode(tanp, INPUT);
        pinMode(logp,INPUT); 
      
      
      }
      
      void loop() {
            answer=bracket_answer(0);         
            Serial.println(answer);
            sujaylcd.setCursor(0,1);
            sujaylcd.print("=");
            sujaylcd.print(answer);
            sujaylcd.setCursor(0,0);
            Serial.println(que.length());
            // sujaylcd.print(que);
            
            int r=0;
            i=0;
            s=0;
            while(r==0){
              val=getval();
                if(val and val=='r'){
                  r=1;
                  s=0;
                  sujaylcd.clear();
                  que='\u0000';
                }
                else if (val and val=='1'){
                  s=0;
                  if((que.length())>16 and i>=0){
                  i++;
                  sujaylcd.setCursor(0,0);
                  sujaylcd.print("                             ");
                  sujaylcd.setCursor(0,0);
                  sujaylcd.print(que.substring(i,i+16));
                  // delay(200);
                  }
                }
                else if (val and val=='2'){
                  s=0;
                  if((que.length())>16 and i>0){
                  i--;
                  sujaylcd.setCursor(0,0);
                  sujaylcd.print("                             ");
                  sujaylcd.setCursor(0,0);
                  sujaylcd.print(que.substring(i,i+15));
                  // delay(200);
                  }
                }  
                else if (val and val=='#'){
                    s=1;
                    Serial.println("changed keypad");
                }
                else;
                
            }
          
      }



      float bracket_answer(int i){
      int b=0;
      int l=i;
      sujaylcd.print(que);
      Serial.println("bracket_answer entered and i=");
      Serial.println(i);
      while(b==0){
         while(ans!=1){
            val=getval();
            Serial.println(val);
            if (val and val=='s'){
              // sujaylcd.clear();
              i++;
              num[i]=getsin();
            }
            else if (val and val=='c'){
              i++;
              // sujaylcd.clear();
              num[i]=getcos();
            }
            else if (val and val=='t'){
              i++;
              // sujaylcd.clear();
              num[i]=gettan();
            }
            if (val and val=='q'){
              // sujaylcd.clear();
              i++;
              num[i]=getsinInv();
            }
            else if (val and val=='b'){
              i++;
              // sujaylcd.clear();
              num[i]=getcosInv();
            }
            else if (val and val=='b'){
              i++;
              // sujaylcd.clear();
              num[i]=getcosInv();
            }
            else if (val and val=='l'){
              i++;
              num[i]=getlog();
            }
            else if (val and val=='o'){
              i++;
              num[i]=getroot();
            }
            else if (val and val=='e'){
              i++;
              num[i]=getexp();
            }
            else if(val and val=='('){
              // sujaylcd.print('(');
              que=que+val;
              sujaylcd.clear();
              // sujaylcd.print('v');
              s=0;
              i++;
              j=i;
              Serial.print(s);
              delay(200);
              num[i+1]=bracket_answer(j-1);
              i=j;
            }
            

           /**************************************get numbers****************************************************************************/
           
            else if(val and val=='0' || val=='1'|| val=='2'|| val=='3'|| val=='4'|| val=='5'
                         || val=='6' || val=='7'|| val=='8'|| val=='9'){
                  int j=0;
                  // sujaylcd.clear();
                  i++;
                  num[i]=0;
                  num[i]=(num[i]*10)+(val-'0');
                  // sujaylcd.print((int)num[i]);
                  printall(val);
              while(j<10){
                char val = getval();
                Serial.println((String)"here"+val);
                if(val and val=='0' || val=='1'|| val=='2'|| val=='3'|| val=='4'|| val=='5'||
                 val=='6'|| val=='7'|| val=='8'|| val=='9' ){
                  Serial.println(val);
                  // sujaylcd.print(val);
                  printall(val);
                  Serial.println(num[i]);
                  num[i]=(num[i]*10)+ (val-'0');
                  Serial.println(num[i]);
                  j++; 
                } 
                else if(val and val=='*'){
                  action[i]='*';
                  // sujaylcd.print('x');
                  printall(val);
                  break;
                }
                else if(val and val=='B'){
                  action[i]='B';
                  // sujaylcd.print('+');
                  printall('+');
                  Serial.println(action[i]); 
                  break;
                }
                else if(val and val=='C'){
                  action[i]='C';
                  // sujaylcd.print('-');
                  printall('-');
                  break;
                }
                else if(val and val=='D'){
                  action[i]='D';
                  // sujaylcd.print('/');
                  printall('/');
                  break;
                }
                else if(val and val=='^'){
                  action[i]='^';
                  // sujaylcd.print('^');
                  printall(val);
                  s=0;
                  break;
                }
                else if(val and val=='A' ){
                  Serial.println("entered");
                  Serial.println("bracket break i=" );
                  Serial.println(i);
                  Serial.println(')');
                  ans=1;
                  break;
                }
                else if(val and val==')'){
                  ans=1;
                  // sujaylcd.print(')');
                  // que=que+val;
                  sujaylcd.clear();
                  printall(val);
                  delay(200);
                  s=0;
                  Serial.println("bracket break i=" );
                  Serial.println(i);
                  break;
                }
                else if(val and val=='#'){
                  delay(200);
                  s++;
                }
              }
              Serial.println(action[i]);
              val=' ';
            }
     /********************************************get num ends**********************************************************************/
            else if(val and val=='*' || val=='D' || val=='B' || val=='C' || val=='^'){
              // action[i]=val;
              if(val and val=='*'){
                  action[i]='*';
                  // sujaylcd.print('x');
                  printall('x');
                  // break;
                }
                else if(val and val=='B'){
                  action[i]='B';
                  // sujaylcd.print('+');
                  printall('+');
                  Serial.println(action[i]); 
                  // break;
                }
                else if(val and val=='C'){
                  action[i]='C';
                  // sujaylcd.print('-');
                  printall('-');
                  // break;
                }
                else if(val and val=='D'){
                  action[i]='D';
                  // sujaylcd.print('/');
                  printall('/');
                  // break;
                }
                else if(val and val=='^'){
                  action[i]='^';
                  // sujaylcd.print('^');
                  printall(val);
                  s=0;
                  // break;
                }
              Serial.println(action[i]);
              Serial.println("sinhere");
              
            }
            else if(val and val=='A' ){
              ans=1;
              Serial.println(action[i]);
             Serial.println("bracket break i=" );
                  Serial.println(i);
              break;
            }
            else if(val and val=='#'){
              s++;
              Serial.print(s);
              Serial.println("changed keys");
              delay(200);
              val=' ';
            }
            else if(val and val==')'){
              // sujaylcd.print(')');
              // printall(val);
              Serial.println("bracket break i=" );
              Serial.println(i);
              ans=1;
              s=0;
              break;
            }
            else if(val and val=='^'){
                  // sujaylcd.print('^');
                  printall(val);
                }
          
            
          }
/******************************************************arrray of numbers collected**********************************************************/
          Serial.println("out of while");
            k=i;
          while(k>0){
            Serial.println(k+(String)"th num is"+num[k]+(String)"action is"+action[k]) ;
            k--;
            }
            Serial.println((String)"0th num is"+num[0]+(String)"action is"+action[0]);
          Serial.println(action[i-1]);
          answer=getanswer1(action,l,i);

          b=1;
          ans=0;
          
      }
       Serial.println((String)"bracket_answer i="+i);
      return answer;
     
      // i=j-1;
    }

      int getangle(){
        int i=0;
        int angle=0;
        while(i<10){
          // Serial.println(val);
          char val = getval();
          Serial.println(val);
          if(val and val=='0' || val=='1'|| val=='2'|| val=='3'|| 
             val=='4'|| val=='5'|| val=='6'|| val=='7'|| val=='8'|| 
             val=='9'){
            Serial.println("angle");
            // int val1=val1 -'0';
            Serial.println(val);
            // delay(500);
            // sujaylcd.setCursor(5+i,0);
            // sujaylcd.print(val);
            printall(val);
            Serial.println(angle);
            angle=(angle*10)+(val-'0');
            Serial.println(angle);
            i++; 
            } 
          else if(val and val==')' and val!='#'){
            sujaylcd.print(")");
            // printall('a');
            que=que+val;
            s=0;
            return angle;
            break;
            }
          else if(val and val=='#'){
            s=1;
          }
         }
       }

      float getanswer1(char action[10],int l,int i){
        // while(i>0){
          int j=i-1;
          Serial.println(i);
          while(j>l){
              
              if(action[j]=='^'){
                Serial.println(i);Serial.println("power");
                    num[j]=pow(num[j],num[j+1]);
                    action[j]=action[j+1];
                    i--;
                    for(k=j+1;k<=i;k++){
                      Serial.println('p');
                      num[k]=num[k+1];
                      action[k]=action[k+1];
                    }
                    j--;
              }
              else {
              j--;
              continue;
              }
          }
           k=i;
            while(k>0){
            Serial.println(k+(String)"th num is"+num[k]+(String)"action is"+action[k]) ;
            k--;
            }
          // while(i>0){
            j=i-1;
          Serial.println(i);
          while(j>l){
              
              if(action[j]=='D'){
                Serial.println(i);Serial.println("Devide");
                    num[j]=(float)num[j]/(float)num[j+1];
                    action[j]=action[j+1];
                    i--;
                    for(k=j+1;k<=i;k++){
                      Serial.println('D');
                      num[k]=num[k+1];
                      action[k]=action[k+1];
                    }
                    j--;
              }
              else {
              j--;
              continue;
              }
          }
           k=i;
            while(k>0){
            Serial.println(k+(String)"th num is"+num[k]+(String)"action is"+action[k]) ;
            k--;
            }
          // while(i>0){
            j=i-1;
            Serial.println(i);
            while(j>l){
                if(action[j]=='*'){
                  Serial.println("multiply");
                      num[j]=num[j]*num[j+1];
                      action[j]=action[j+1];
                      i--;
                      for(k=j+1;k<=i;k++){
                        num[k]=num[k+1];
                        action[k]=action[k+1];
                      } 
                      j--; 
                } 

                else {
                j--;
                continue;
                }
            }  
             k=i;
            while(k>l){
            Serial.println(k+(String)"th num is"+num[k]+(String)"action is"+action[k]) ;
            k--;
            }
          // while(i>0){
            j=i-1;
            Serial.println(i);
            while(j>l){
              Serial.println(i);
              if(action[j]=='C'){
                Serial.println("minus");
                      num[j]=num[j]-num[j+1];
                      action[j]=action[j+1];
                      i--;
                      for(k=j+1;k<=i;k++){
                        num[k]=num[k+1];
                        action[k]=action[k+1];
                      } 
                      j--; 
                  } 
                  else {
                  j--;
                  continue;
                  }
            }
             k=i;
            while(k>0){
            Serial.println(k+(String)"th num is"+num[k]+(String)"action is"+action[k]) ;
            k--;
            }
          // while(i>0){
            j=i-1;
            Serial.println(i);
            while(j>l){
               Serial.println('E1');
               if(action[j]=='B'){
                 Serial.println("plus");
                        num[j]=num[j]+num[j+1];
                        action[j]=action[j+1];
                        i--;
                        Serial.println('E2');
                        for(k=j+1;k<=i;k++){
                          num[k]=num[k+1];
                          Serial.println('E3');
                          action[k]=action[k+1];
                        }  
                        j--;
                   } 
                   else{
                  j--;
                  continue;
                   }
            }
             k=i;
            while(k>0){
            Serial.println(k+(String)"th num is"+num[k]+(String)"action is"+action[k]) ;
            k--;
            }
            Serial.println((String)"get answer i="+i);
        return num[i];
      }




      float getsin(){
            sujaylcd.print("sin\(");
            que=que+"sin\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            sina = sin(angle*DEG_TO_RAD);
            Serial.println((String)"sina="+sina);
            return sina;
        
      }
      float getcos(){
            sujaylcd.print("cos\(");
            que=que+"cos\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            cosa = cos(angle*DEG_TO_RAD);
            Serial.println((String)"cosa="+cosa);
            return cosa;
        
      }
      float gettan(){
            sujaylcd.print("tan\(");
            que=que+"tan\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            tana = tan(angle*DEG_TO_RAD);
            Serial.println((String)"tana="+tana);
            return tana;
        
      }


      float getsinInv(){
            sujaylcd.print("sinInv\(");
            que=que+"sinInv\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            asina = asin(angle)*RAD_TO_DEG;
            Serial.println((String)"sininva="+sina);
            return asina;
        
      }
      float getcosInv(){
            sujaylcd.print("cosInv\(");
            que=que+"cosInv\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            acosa = cos(angle)*RAD_TO_DEG;
            Serial.println((String)"cosInva="+cosa);
            return acosa;
        
      }
      float gettanInv(){
            sujaylcd.print("tanInv\(");
            que=que+"tanInv\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            atana = tan(angle)*RAD_TO_DEG;
            Serial.println((String)"atana="+tana);
            return atana;
        
      }
      float getlog(){
            sujaylcd.print("log\(");
            que=que+"log\(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            loga = log(angle);
            Serial.println((String)"loga="+loga);
            return loga;
        
      }
      float getroot(){
            sujaylcd.print("sqrt\(");
            que=que+"sqrt(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            root = sqrt(angle);
            Serial.println((String)"root="+root);
            return root;
        
      }
      float getexp(){
            sujaylcd.print("exp\(");
            que=que+"exp(";
            s=0;
            angle=getangle();  
            Serial.println(angle);                                                                                       
            expa = exp(angle);
            Serial.println((String)"exp="+expa);
            return expa;
        
      }
      char getval(){
         
            if(s==0){
              val=keysujay.getKey();
            }
            else{
              val=keysujay1.getKey();
              
            }
          
            return val;
      }
      void printall(char val){
          que=que+val;
          sujaylcd.clear();
          // sujaylcd.print("p");
          if((que.length())>16 and i>=0){
              i++;
              sujaylcd.setCursor(0,0);
              sujaylcd.print("                             ");
              sujaylcd.setCursor(0,0);
              sujaylcd.print(que.substring(i,i+16));
              // delay(200);
              }
          else{
              sujaylcd.setCursor(0,0);
              sujaylcd.print(que);
              // sujaylcd.print('q');
          }
          
      }
