// Projet de programme de traduction du code morse

// Variables intervalles
int delaiEntreAcquisition = 300;
byte seuilPressionLong    = 2;
byte seuilFinAcquisition  = 10;

// Variables fonctionnement
byte compteurPression = 0;
byte compteurLeve     = 0;
byte caractere[5]     = {0};
byte idxPression      = 0;
byte reference[5]     = {0};
byte comparaison      = 0;

void setup() {
  // Frequence de lecture pour le debug
  Serial.begin(9600);
  
}


/////////////////////////////////////////////////////

void loop() {
  // Intervalle de temps entre chaque acquisition
  delay(delaiEntreAcquisition);
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
  else if(compteurPression > 0) {
    // appui long
    if (compteurPression > seuilPressionLong){
      caractere[idxPression] = 2;
      idxPression = idxPression+1;
    }
    // appui court
    else {
      caractere[idxPression] = 1;
      idxPression = idxPression+1;
    }
    Serial.println(caractere[idxPression-1]);
    compteurLeve = compteurLeve+1;
    compteurPression = 0;
  }

  // bouton leve
  else{
    // Reglage compteurs
    compteurLeve = compteurLeve+1;
  }

  // Affichage //////////////////////////////////////
  // depouillement
  if ((compteurLeve > seuilFinAcquisition || caractere[4]) != 0 && caractere[0] != 0){
    depouillement(caractere);
    
  // Remise a 0
    for (byte i = 0; i < 5; i++) { 
      caractere[i] = 0;
    }
    compteurPression = 0;
    compteurLeve = 0;
    idxPression = 0;
  }
}

// FONCTIONS //////////////////////////////////////////
// Fonction permettant de comparer 2 vecteurs
byte comparaisonVecteurs(byte vecteur1[], byte vecteur2[], byte taille){
  for (byte i = 0; i < taille; i++){
    if (vecteur1[i] != vecteur2[i]){
      return 0;
      break;
    }
  }
  // Si les 2 vecteurs sont egaux
  return 1;
}

// Fonction interpretant le caractere a partir de la suite de signaux
void depouillement(byte caractere[]){

  // espace {2, 1, 1, 1, 2}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 2;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('_');
  }
  // A {1, 2, 0, 0, 0}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 0;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('A');
  }
  // B {2, 1, 1, 1, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('B');
  }
  // C {2, 1, 2, 1, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 2;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('C');
  }
  // D {2, 1, 1, 0, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('D');
  }
  // E {1, 0, 0, 0, 0}
  reference[0] = 1;
  reference[1] = 0;
  reference[2] = 0;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('E');
  }
  // F {1, 1, 2, 1, 0}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 2;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('F');
  }
  // G {2, 2, 1, 0, 0}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 1;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('G');
  }
  // H {1, 1, 1, 1, 0}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('H');
  }
  // I {1, 1, 0, 0, 0}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 0;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('I');
  }
  // J {1, 2, 2, 2, 0}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 2;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('J');
  }
  // K {2, 1, 2, 0, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 2;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('K');
  }
  // L {1, 2, 1, 1, 0}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('L');
  }
  // M {2, 2, 0, 0, 0}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 0;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('M');
  }
  // N {2, 1, 0, 0, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 0;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('N');
  }
  // O {2, 2, 2, 0, 0}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('O');
  }
  // P {1, 2, 2, 1, 0}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('P');
  }
  // Q {2, 2, 1, 2, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('Q');
  }
  // R {1, 2, 1, 0, 0}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 1;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('R');
  }
  // S {1, 1, 1, 0, 0}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('S');
  }
  // T {2, 0, 0, 0, 0}
  reference[0] = 2;
  reference[1] = 0;
  reference[2] = 0;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('T');
  }
  // U {1, 1, 2, 0, 0}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 2;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('U');
  }
  // V {1, 1, 1, 2, 0}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 2;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('V');
  }
  // W {1, 2, 2, 0, 0}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 0;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('W');
  }
  // X {2, 1, 1, 2, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 2;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('X');  
  }
  // Y {2, 1, 2, 2, 0}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 2;
  reference[3] = 2;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('Y');
  }
  // Z {2, 2, 1, 1, 0}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('Z');
  }
  // 1 {1, 2, 2, 2, 2}
  reference[0] = 1;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 2;
  reference[4] = 2;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('1');
  }
  // 2 {1, 1, 2, 2, 2}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 2;
  reference[3] = 2;
  reference[4] = 2;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('2');
  }
  // 3 {1, 1, 1, 2, 2}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 2;
  reference[4] = 2;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('3');
  }
  // 4 {1, 1, 1, 1, 2}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 2;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('4');
  }
  // 5 {1, 1, 1, 1, 1}
  reference[0] = 1;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 1;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('5');
  }
  // 6 {2, 1, 1, 1, 1}
  reference[0] = 2;
  reference[1] = 1;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 1;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('6');
  }
  // 7 {2, 2, 1, 1, 1}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 1;
  reference[3] = 1;
  reference[4] = 1;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('7');
  }
  // 8 {2, 2, 2, 1, 1}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 1;
  reference[4] = 1;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('8');
  }
  // 9 {2, 2, 2, 2, 1}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 2;
  reference[4] = 1;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('9');
  }
  // 0 {2, 2, 2, 2, 2}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 2;
  reference[3] = 2;
  reference[4] = 2;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('0');
  }
}
