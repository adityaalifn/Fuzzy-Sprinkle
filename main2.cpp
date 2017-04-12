#include <iostream>

using namespace std;

struct arrayInference{
    double nilai;
    string label;
};

typedef struct arrayInference rule;
rule rule1, rule2, rule3, rule4, arr[3];
/*typedef struct arrayInference rule2;
typedef struct arrayInference rule3;
typedef struct arrayInference rule4;
typedef struct arrayInference arr[3];*/

string tentukan_rule(string y, string x){
    if (x == "Basah"){
        return "Singkat";
    } else if (x == "Lembab"){
        if (y=="Dingin" || y=="Sejuk"){
            return "Singkat";
        }else {
            return "Sedang";
        }
    }else if (x=="Kering"){
            return "Lama";
    }
    return "";
}
double konjungsi(double y, double x) {
    if (y <= x) {
        return y;
    }
    else {
        return x;
    }
}


int main()
{
    double suhu,miuSuhu1,miuSuhu2,kelembapan,miuLembab1,miuLembab2 = 0;
    string label1suhu,label2suhu,label1lembab,label2lembab = " "; //label1 turun label2 naik
    //double rulenilai1, rulenilai2, rulenilai3, rulenilai4;
    cout<<"Masukkan Suhu: ";
    cin>>suhu;
    if (suhu <= 0){
        miuSuhu1 = 1;
        label1suhu = "Dingin";
        miuSuhu2 = 0;
    }
    else if ((suhu >= 3) && (suhu <= 12)){
        miuSuhu1 = 1;
        label1suhu = "Sejuk";
        miuSuhu2 = 0;
    }
    else if ((suhu >= 15) && (suhu <= 24)){
        miuSuhu1 = 1;
        label1suhu = "Normal";
        miuSuhu2 = 0;
    }
    else if ((suhu >= 27) && (suhu <= 36)){
        miuSuhu1 = 1;
        label1suhu = "Hangat";
        miuSuhu2 = 0;
    }
    else if (suhu >= 39){
        miuSuhu1 = 1;
        label1suhu = "Panas";
        miuSuhu2 = 0;
    }
    else if ((suhu > 0) && (suhu < 3)){
        miuSuhu1 = -((suhu-3)/(3-0));
        label1suhu = "Dingin";
        miuSuhu2 = ((suhu-0)/3-0);
        label2suhu = "Sejuk";
    }
    else if ((suhu > 12) && (suhu < 15)){
        miuSuhu1 = -((suhu-15)/(15-12));
        label1suhu = "Sejuk";
        miuSuhu2 = ((suhu-12)/(15-12));
        label2suhu = "Normal";
    }
    else if ((suhu > 24) && (suhu < 27)){
        miuSuhu1 = -((suhu-27)/(27-24));
        label1suhu = "Normal";
        miuSuhu2 = ((suhu-24)/(27-24));
        label2suhu = "Hangat";
    }
    else if ((suhu > 36) && (suhu < 39)){
        miuSuhu1 = -((suhu-39)/(39-36));
        label1suhu = "Hangat";
        miuSuhu2 = ((suhu-36)/(39-36));
        label2suhu = "Panas";
    }

    //Menghitung kelembaban
    cout<<"Masukan Kelembapan: ";
    cin>>kelembapan;
    if (kelembapan<=10){
        miuLembab1 = 1;
        label1lembab = "Kering";
        miuLembab2 = 0;
    }
    else if ((kelembapan>=20) && (kelembapan <=40)){
        miuLembab1 = 1;
        label1lembab = "Lembab";
        miuLembab2 = 0;
    }
    else if (kelembapan >=50){
        miuLembab1 = 1;
        label1lembab = "Basah";
        miuLembab2 = 0;
    }
    else if ((kelembapan > 10) && (kelembapan <20)){
        miuLembab1 = -((kelembapan-20)/(20-10));
        label1lembab = "Kering";
        miuLembab2 = (kelembapan-10)/(20-10);
        label2lembab = "Lembab";
    }
    else if ((kelembapan >20) && (kelembapan <40)){
        miuLembab1 = -((kelembapan-50)/(50-40));
        label1lembab = "Lembap";
        miuLembab2 = (kelembapan-40)/(50-40);
        label2lembab = "Basah";
    }

    if ((miuLembab2 == 0) && (miuSuhu2 == 0)){
        cout<<label1suhu<<"("<<miuSuhu1<<")"<<endl;
        cout<<label1lembab<<"("<<miuLembab1<<")"<<endl;
    }
    else if (miuSuhu2 == 0){
        cout<<label1suhu<<"("<<miuSuhu1<<")"<<endl;
        cout<<label1lembab<<"("<<miuLembab1<<")"<<endl;
        cout<<label2lembab<<"("<<miuLembab2<<")";
    }
    else if (miuLembab2 == 0){
        cout<<label1suhu<<"("<<miuSuhu1<<")"<<endl;
        cout<<label2suhu<<"("<<miuSuhu2<<")"<<endl;
        cout<<label1lembab<<"("<<miuLembab1<<")"<<endl;
    }
    else{
        cout<<label1suhu<<"("<<miuSuhu1<<")"<<endl;
        cout<<label2suhu<<"("<<miuSuhu2<<")"<<endl;
        cout<<label1lembab<<"("<<miuLembab1<<")"<<endl;
        cout<<label2lembab<<"("<<miuLembab2<<")";
    }

    //inference

    rule1.label =tentukan_rule(label1suhu,label1lembab);
    rule2.label =tentukan_rule(label1suhu,label2lembab);
    rule3.label =tentukan_rule(label2suhu,label1lembab);
    rule4.label =tentukan_rule(label2suhu,label2lembab);
    rule1.nilai =konjungsi(miuSuhu1,miuLembab1);
    rule2.nilai =konjungsi(miuSuhu1,miuLembab2);
    rule3.nilai =konjungsi(miuSuhu2,miuLembab1);
    rule4.nilai =konjungsi(miuSuhu2,miuLembab2);
    cout << endl;
    cout << "IF "<< label1suhu<<" ("<<miuSuhu1<<") AND " << label1lembab<< " ("<<miuLembab1<<") THEN "<<rule1.label<< "("<<rule1.nilai<<")" <<endl;
    cout << "IF "<< label1suhu<<" ("<<miuSuhu1<<") AND " << label2lembab<< " ("<<miuLembab2<<") THEN "<<rule2.label<< "("<<rule2.nilai<<")" <<endl;
    cout << "IF "<< label2suhu<<" ("<<miuSuhu2<<") AND " << label1lembab<< " ("<<miuLembab1<<") THEN "<<rule3.label<< "("<<rule3.nilai<<")" <<endl;
    cout << "IF "<< label2suhu<<" ("<<miuSuhu2<<") AND " << label2lembab<< " ("<<miuLembab2<<") THEN "<<rule4.label<< "("<<rule4.nilai<<")" <<endl;


    arr[0].label = rule1.label;
    arr[0].nilai = rule1.nilai;
    for (int i=1; i<2;i++){
        if(rule3.label !=arr[i].label){
            arr[i].label=rule3.label;
        }else {
            if (arr[i].nilai < rule3.nilai){
                arr[i].nilai = rule3.nilai;
            }
        }
    }
    for (int i=1; i<2;i++){
        if (rule2.label!=arr[i].label){
            arr[i].label=rule2.label;
        }else {
            if (arr[i].nilai < rule2.nilai){
                arr[i].nilai = rule2.nilai;
            }
        }
    }
    for (int i=1; i<2;i++){
        if(rule4.label!=arr[i].label) {
            arr[i].label=rule2.label;
        }else {
            if (arr[i].nilai < rule4.nilai){
                arr[i].nilai = rule4.nilai;
            }
        }
    }

    double hasil;
    for (int i=0; i<3; i++){
        if (arr[i].nilai != 0){
            cout<<arr[i].label<<"("<<arr[i].nilai<<")"<<endl;
            if (arr[i].label == "Singkat"){
                hasil += arr[i].nilai * 20;
            }
            else if (arr[i].label == "Sedang"){
                hasil += arr[i].nilai * 40;
            }
            else if (arr[i].label == "Lama"){
                hasil += arr[i].nilai * 60;
            }
        }
    }

    cout<<hasil;

    return 0;
}
