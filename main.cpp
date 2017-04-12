#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

struct arrayFuzzy{
    double nilai;
    string label;
};

typedef struct arrayFuzzy fuzzy;

fuzzy suhuF[2],lembabF[2],rule[4],infer[3];

string tentukan_rule(string y, string x);
void tentukanSuhu(double suhu);
void tentukanLembab(double kelembapan);
double konjungsi(double y, double x);

int main()
{
    double hasil;
    //Menghitung suhu
    double suhu;
    cout<<"Masukkan Suhu: ";
    cin>>suhu;
    tentukanSuhu(suhu);

    //Menghitung kelembaban
    double kelembapan;
    cout<<"Masukan Kelembapan: ";
    cin>>kelembapan;
    tentukanLembab(kelembapan);

    //output fuzzfication
    cout<<"******* FUZZYFICATION *******"<<endl;
    for (int i=0; i<2; i++){
        if (suhuF[i].nilai != 0){
            cout<<suhuF[i].label<<"("<<suhuF[i].nilai<<")"<<endl;
        }
    }

    for (int i=0; i<2; i++){
        if (lembabF[i].nilai != 0){
            cout<<lembabF[i].label<<"("<<lembabF[i].nilai<<")"<<endl;
        }
    }
    cout<<endl;

    //inference
    cout<<"******* INFERENCE *******"<<endl;
    //konjungsi
    for (int i=0; i<4; i++){
        for (int j=0; i<2; i++){
            rule[i].label = tentukan_rule(suhuF[i].label,lembabF[j].label);
            rule[i].nilai = konjungsi(suhuF[i].nilai,lembabF[j].nilai);
        }
    }

    //output hasil konjungsi
    for (int i=0; i<4; i++){
        if (rule[i].nilai != 0){
            cout<<"IF "<<suhuF[i].label<<" ("<<suhuF[i].nilai<<") AND "<<lembabF[i].label<<" ("<<lembabF[i].nilai<<") THEN "<<rule[i].label<<"("<<rule[i].nilai<<")"<<endl;
        }
    }

    //disjungsi
    infer[0] = rule[0];
    for (int i=1; i<3; i++){
        for (int j=i; j<4; j++){
            if (infer[i].label == rule[j].label){
                if (infer[i].nilai < rule[j].nilai){
                    infer[i].nilai = rule[j].nilai;
                }
            }
            else{
                infer[i] = rule[j];
            }
        }
    }

    //output hasil disjungsi
    for (int i=0; i<3; i++){
        if(infer[i].nilai != 0){
            cout<<infer[i].label<<" "<<infer[i].nilai<<endl;
            if (infer[i].label == "Singkat"){
                hasil += infer[i].nilai * 20;
            }
            else if (infer[i].label == "Sedang"){
                hasil += infer[i].nilai * 40;
            }
            else if (infer[i].label == "Lama"){
                hasil += infer[i].nilai * 60;
            }
        }
    }
    cout<<endl<<"******* DEFUZZYFICATION *******"<<endl;
    cout<<"Lama Springkle Menyiram: "<<hasil<<" Menit"<<endl;
    return 0;
}

void tentukanSuhu(double suhu){
    if (suhu <= 0){
        suhuF[0].nilai = 1;
        suhuF[0].label = "Dingin";
        suhuF[1].nilai = 0;
    }
    else if ((suhu >= 3) && (suhu <= 12)){
        suhuF[0].nilai = 1;
        suhuF[0].label = "Sejuk";
        suhuF[1].nilai = 0;
    }
    else if ((suhu >= 15) && (suhu <= 24)){
        suhuF[0].nilai = 1;
        suhuF[0].label = "Normal";
        suhuF[1].nilai = 0;
    }
    else if ((suhu >= 27) && (suhu <= 36)){
        suhuF[0].nilai = 1;
        suhuF[0].label = "Hangat";
        suhuF[1].nilai = 0;
    }
    else if (suhu >= 39){
        suhuF[0].nilai = 1;
        suhuF[0].label = "Panas";
        suhuF[1].nilai = 0;
    }
    else if ((suhu > 0) && (suhu < 3)){
        suhuF[0].nilai = -((suhu-3)/(3-0));
        suhuF[0].label = "Dingin";
        suhuF[1].nilai = ((suhu-0)/3-0);
        suhuF[1].label = "Sejuk";
    }
    else if ((suhu > 12) && (suhu < 15)){
        suhuF[0].nilai = -((suhu-15)/(15-12));
        suhuF[0].label = "Sejuk";
        suhuF[1].nilai = ((suhu-12)/(15-12));
        suhuF[1].label = "Normal";
    }
    else if ((suhu > 24) && (suhu < 27)){
        suhuF[0].nilai = -((suhu-27)/(27-24));
        suhuF[0].label = "Normal";
        suhuF[1].nilai = ((suhu-24)/(27-24));
        suhuF[1].label = "Hangat";
    }
    else if ((suhu > 36) && (suhu < 39)){
        suhuF[0].nilai = -((suhu-39)/(39-36));
        suhuF[0].label = "Hangat";
        suhuF[1].nilai = ((suhu-36)/(39-36));
        suhuF[1].label = "Panas";
    }
}

void tentukanLembab(double kelembapan){
        if (kelembapan<=10){
        lembabF[0].nilai = 1;
        lembabF[0].label = "Kering";
        lembabF[1].nilai = 0;
    }
    else if ((kelembapan>=20) && (kelembapan <=40)){
        lembabF[0].nilai = 1;
        lembabF[0].label = "Lembab";
        lembabF[1].nilai = 0;
    }
    else if (kelembapan >=50){
        lembabF[0].nilai = 1;
        lembabF[0].label = "Basah";
        lembabF[1].nilai = 0;
    }
    else if ((kelembapan > 10) && (kelembapan <20)){
        lembabF[0].nilai = -((kelembapan-20)/(20-10));
        lembabF[0].label = "Kering";
        lembabF[1].nilai = (kelembapan-10)/(20-10);
        lembabF[1].label = "Lembab";
    }
    else if ((kelembapan >20) && (kelembapan <40)){
        lembabF[0].nilai = -((kelembapan-50)/(50-40));
        lembabF[0].label = "Lembap";
        lembabF[1].nilai = (kelembapan-40)/(50-40);
        lembabF[1].label = "Basah";
    }
}

string tentukan_rule(string y, string x){
    if (x == "Basah"){
        return "Singkat";
    }
    else if (x == "Lembab"){
        if (y=="Dingin" || y=="Sejuk"){
            return "Singkat";
        }
        else {
            return "Sedang";
        }
    }
    else if (x=="Kering"){
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
    return 0;
}
