#include <bits/stdc++.h>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void process(std::string name,std::string codename, int type){
    int width, height, channels;
    unsigned char* foto = stbi_load(name.c_str(), &width, &height, &channels, 0);
    if (!foto) {
        std::cerr << "\npor favor fazer o favor de fazer garantir que a imagem que voce colocou exista na pasta seu porra\n" << endl;
    }
    else{
        std::cout << "\ndimensões do arquivo:" << width << "x" << height << " | ";
        if (channels == 3){
            std::string line;
            std::string finalP;

            int totalSize = width*height;
            std::ifstream brainFuck(codename);
            std::string code = "";
            int codeSize = 0;
            std::string codeline = "";

            while(std::getline(brainFuck, codeline)){
                code += codeline;
            }

            codeSize = code.size();
            int averagepos = totalSize/codeSize;

            if (averagepos < 30){
                std::cout << "por favor pare de fazer demandas irrazoaveis. Dame espaco pra trabalhare agradeco desde entao." << endl;
                return;
            }

            //Caracteres por brilho: $@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'.
            static const std::array<int,12> values = {234, 213, 192, 171, 150, 129, 108, 87, 66 ,45 ,24, -900};
            static const std::array<char, 12> c =  {'$','%','W','o','Z','v','{','1','?','!',':','\''};
            std::unordered_map<char, char> relations = {{'#', '$'},{'[', '1'},{']', '1'},{'-','?'},{'+','?'},{'>','!'},{'<','!'},{',',':'},{'.','\''}};
            int codePos = 0;

            for (int k = 0; k < height; k++){
                for(int j = 0; j < width; j++){

                    int i = (k * width + j) * channels;
                    unsigned char r = foto[i];
                    unsigned char g = foto[i+1];
                    unsigned char b = foto[i+2];
                    float brightness;
                    if (type == 0){
                        brightness = 0.299f * r + 0.587f * g + 0.114f * b;
                    }
                    else if (type == 1){
                        brightness = 0.2126f * r + 0.7152f * g + 0.0722f * b;
                    }
                    else{
                        brightness = sqrt(0.299f*r*r + 0.587f*g*g + 0.114f*b*b);
                    }

                    for(int i = 0; i < 12; i++){
                        if (brightness > values[i]){
                            if (relations[code[codePos]] == c[i]){
                                line += code[codePos];
                                codePos++;
                            }
                            else{
                                line += c[i];
                            }        
                            break;
                        }
                    }
                }
                finalP += line;
                finalP += "\n";
                line = "";
            }

            if (codePos < codeSize){
                std::cout << "se liga precisei fazer um troco q tu talvez n goste, mas assim, só aumentar a imagem ou diminuir a mensagem (rimas) para resolver isase" << endl;
                int rest = codeSize - codePos;

                for (int s = 0; s< rest; s++){
                    finalP += code[codeSize-rest+s];
                    
                    if (s % width == 0 && s != 0){
                        finalP += "\n";
                    }
                }
            }

            std::string ftNome = name.erase(name.size()-4);
            ftNome += ".txt";
            std::ofstream fw(ftNome);
            if (!fw){
                std::cerr << ("nao deu de achar o out.txt eu tentei mas nao consegui acho que voce deve ter feito algo nao muito legal que deve ter afetado minhas capacidades de achar esse tal de arquivo ae obrigado desde entao.");
            }
            fw << finalP;
            fw.close();

            std::cout << "Confira '"<< ftNome <<"' para ver resultado.\n"<< endl;
            finalP = "";


            stbi_image_free(foto);
        }
        else{
            std::cout << "quantia de canais indevida!" << endl;
        }
    }
    
}

int main(){
    while (true){
        std::string filename;
        std::string codename;
        int type;
        std::cout << "Digite o nome da foto para prosseguir -->";
        std::cin >> filename;
        std::cout << "Digite o nome do arquivo do código para prosseguir -->";
        std::cin >> codename;
        std::cout << "Escolha o leitor de brilho (0, 1, 2)     -->";
        std::cin >> type;

        process(filename, codename, type);
    }
    return 0;
}