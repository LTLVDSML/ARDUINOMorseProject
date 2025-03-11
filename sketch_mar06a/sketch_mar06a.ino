// Projet de programme de traduction du code morse

// Variables intervalles
int delaiEntreAcquisition = 300;
byte seuilPressionLong    = 3;
byte seuilFinAcquisition  = 10;

// Definition des pins
#define haut_droite 2
#define haut_centre 3
#define haut_gauche 4
#define centre      5
#define point       6
#define bas_droite  7
#define bas_centre  8
#define bas_gauche  9
#define analog      A1

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

  // Definition pins
  pinMode(haut_droite, OUTPUT); 
  pinMode(haut_centre, OUTPUT);
  pinMode(haut_gauche, OUTPUT);
  pinMode(centre,      OUTPUT);
  pinMode(point,       OUTPUT); 
  pinMode(bas_droite,  OUTPUT);
  pinMode(bas_centre,  OUTPUT);
  pinMode(bas_gauche,  OUTPUT);

  digitalWrite(haut_droite, LOW); 
  digitalWrite(haut_centre, LOW);
  digitalWrite(haut_gauche, LOW);
  digitalWrite(centre,      LOW);
  digitalWrite(point,       LOW); 
  digitalWrite(bas_droite,  LOW);
  digitalWrite(bas_centre,  LOW);
  digitalWrite(bas_gauche,  LOW);
  
}


/////////////////////////////////////////////////////

void loop() {
  // Intervalle de temps entre chaque acquisition
  delay(delaiEntreAcquisition);
  byte bouton = analogRead(analog);
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
    digitalWrite(point,       HIGH); 
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
    affichageSegment('a');
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
    affichageSegment('b');
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
    affichageSegment('c');
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
    affichageSegment('d');
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
    affichageSegment('e');
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
    affichageSegment('f');
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
    affichageSegment('g');
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
    affichageSegment('h');
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
    affichageSegment('i');
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
    affichageSegment('j');
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
    affichageSegment('k');
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
    affichageSegment('l');
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
    affichageSegment('m');
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
    affichageSegment('n');
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
    affichageSegment('o');
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
    affichageSegment('p');
  }
  // Q {2, 2, 1, 2, 0}
  reference[0] = 2;
  reference[1] = 2;
  reference[2] = 1;
  reference[3] = 2;
  reference[4] = 0;
  comparaison =  comparaisonVecteurs(caractere, reference, 5);
  if (comparaison == 1){
    Serial.println('Q');
    affichageSegment('q');
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
    affichageSegment('r');
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
    affichageSegment('s');
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
    affichageSegment('t');
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
    affichageSegment('u');
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
    affichageSegment('v');
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
    affichageSegment('w');
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
    affichageSegment('x');  
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
    affichageSegment('y');
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
    affichageSegment('z');
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
    affichageSegment('1');
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
    affichageSegment('2');
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
    affichageSegment('3');
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
    affichageSegment('4');
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
    affichageSegment('5');
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
    affichageSegment('6');
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
    affichageSegment('7');
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
    affichageSegment('8');
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
    affichageSegment('9');
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
    affichageSegment('0');
  }
}

// Fonction permettant l'affichage des nombres sur l'afficheur 7 segments
void affichageSegment(char valeur){
  
  // Reset of the display
  digitalWrite(haut_droite, LOW); 
  digitalWrite(haut_centre, LOW);
  digitalWrite(haut_gauche, LOW);
  digitalWrite(centre,      LOW);
  digitalWrite(point,       LOW); 
  digitalWrite(bas_droite,  LOW);
  digitalWrite(bas_centre,  LOW);
  digitalWrite(bas_gauche,  LOW);
  
  switch (valeur) {
    case '0':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case '1':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    break;

    case '2':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(centre,      HIGH); 
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    break;

    case '3':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(centre,      HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    break;

    case '4':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_gauche, HIGH);
    digitalWrite(centre,      HIGH); 
    digitalWrite(bas_droite,  HIGH);
    break;  

    case '5':
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(centre,      HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    break;

    case '6':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(centre,      HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case '7':
    digitalWrite(haut_centre, HIGH); 
    digitalWrite(haut_droite, HIGH);
    digitalWrite(bas_droite,  HIGH);
    break;

    case '8':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case '9':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(centre,      HIGH);
    break;
    
    case 'a':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'b':
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'c':
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'd':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'e':
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'f':
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'g':
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'h':
    digitalWrite(haut_droite, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'i':
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'j':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    break;

    case 'k':
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'l':
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'm':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'n':
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'o':
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'p':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'q':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'r': 
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 's':
    digitalWrite(haut_centre, HIGH);
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 't':
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'u':
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'v':
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'w':
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    break;

    case 'x':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'y':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_gauche, HIGH); 
    digitalWrite(bas_droite,  HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    case 'z':
    digitalWrite(haut_droite, HIGH); 
    digitalWrite(haut_centre, HIGH);
    digitalWrite(bas_centre,  HIGH);
    digitalWrite(bas_gauche,  HIGH);
    digitalWrite(centre,      HIGH);
    break;

    
  }
  
}
