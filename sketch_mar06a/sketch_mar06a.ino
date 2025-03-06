// Projet de programme de traduction du code morse

// Variables fonctionnement
byte compteurPression = 0;
byte compteurLeve = 0;
byte caractere[5] = {0};
byte idxPression = 0;

void setup() {
  // Frequence de lecture pour le debug
  Serial.begin(9600);
  
}


/////////////////////////////////////////////////////

void loop() {
  // Intervalle de temps entre chaque acquisition
  delay(200);
  byte bouton = analogRead(A0);
  //Serial.println(bouton);

  // Traitements ////////////////////////////////////
  // bouton presse
  if (bouton < 200){

    // Reglage compteurs
    compteurPression = compteurPression+1;
    compteurLeve = 0;
  }

  
  // bouton leve apres appui
  else if(compteurPression>0) {
    // appui long
    if (compteurPression>4){
      caractere[idxPression] = 2;
      idxPression = idxPression+1;
    }
    // appui court
    else {
      caractere[idxPression] = 1;
      idxPression = idxPression+1;
    }
    Serial.println(caractere[idxPression]);
    compteurLeve = compteurLeve+1;
    compteurPression = 0;
  }

  // bouton leve
  else{
    // Reglage compteurs
    compteurLeve = compteurLeve+1;
  }
  
}
