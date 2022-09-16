#include <iostream>
#include <string>
#include <map>
#include <fstream>

std::string BOOK;
std::string CHAPTER;
std::string FIRSTVERSE;
int LASTVERSE;

std::string bookName(const std::string& abbreviation) {
    std::map<std::string, std::string> books = {
            {"Rdz", "Rodzaju"},
            {"Wj", "Wyjścia"},
            {"Kpł", "Kapłańska"},
            {"Lb", "Liczb"},
            {"Pwt", "Powtórzonego Prawa"},
            {"Joz", "Jozuego"},
            {"Sdz", "Sędziów"},
            {"Rt", "Rut"},
            {"1Sm", "1 Samuela"},
            {"2sm", "2 Samuela"},
            {"1Krl", "1 Królewska"},
            {"2Krl", "2 Królewska"},
            {"1Krn", "1 Kronik"},
            {"2Krn", "2 Kronik"},
            {"Ezd", "Ezdrasza"},
            {"Ne","Nehemiasza"},
            {"Tb","Tobiasza"},
            {"Jdt","Judyty"},
            {"Est","Estery"},
            {"1Mch","1 Machabejska"},
            {"2Mch","2 Machabejska"},
            {"Hi","Hioba"},
            {"Ps","Psalmów"},
            {"Prz", "Przysłów"},
            {"Koh", "Koheleta"},
            {"Pnp", "Pieśń nad Pieśniami"},
            {"Mdr", "Mądrości"},
            {"Syr", "Syracha"},
            {"Iz", "Izajasza"},
            {"Jr", "Jeremiasza"},
            {"Lm", "Lamentacje"},
            {"Ba", "Barucha"},
            {"Ez", "Ezechiela"},
            {"Dn", "Daniela"},
            {"Oz", "Ozeasza"},
            {"Jl", "Joela"},
            {"Am", "Amosa"},
            {"Ab", "Abdiasza"},
            {"Jon", "Jonasza"},
            {"Mi", "Michaesza"},
            {"Na", "Nahuma"},
            {"Ha", "Habakuka"},
            {"So", "Sofoniasza"},
            {"Ag", "Aggeusza"},
            {"Za", "Zachariasza"},
            {"Ml", "Malachiasza"},
            {"Mt", "Ewangelia wg św. Mateusza"},
            {"Mk", "Ewangelia wg św. Marka"},
            {"Łk", "Ewangelia wg św. Łukasza"},
            {"J", "Ewangelia wg św. Jana"},
            {"Dz", "Dzieje Apostolskie"},
            {"Rz", "List do Rzymian"},
            {"1Kor", "1 List do Koryntian"},
            {"2Kor", "2 List do Koryntian"},
            {"Ga", "List do Galatów"},
            {"Ef", "List do Efezjan"},
            {"Flp", "List do Filipian"},
            {"Kol", "List do Kolosan"},
            {"1Tes", "1 List do Tesaloniczan"},
            {"2Tes", "2 List do Tesaloniczan"},
            {"1Tm", "1 List do Tymoteusza"},
            {"2Tm", "2 List do Tymoteusza"},
            {"Tt", "List do Tytusa"},
            {"Flm", "List do Filemona"},
            {"Hbr", "List do Hebrajczyków"},
            {"Jk", "List św. Jakuba"},
            {"1P", "1 List św. Piotra"},
            {"2P", "2. List św. Piotra"},
            {"1J", "1 List św. Jana"},
            {"2J", "2 List św. Jana"},
            {"3J", "3 List św. Jana"},
            {"Jud", "List św. Judy"},
            {"Ap", "Apokalipsa św. Jana"},
    };
    return books[abbreviation];
}

void siglumParser(std::string siglum) {
    std::string chapter;
    std::string verses;
    std::string book;
    std::string lastVerse;

    int lastVerseNum;

    std::string eoc = ",";
    std::string eob = " ";
    std::string eov = "-";

    std::size_t eoc_pos = siglum.find(eoc);
    if(eoc_pos != std::string::npos) {
        verses = siglum.substr(eoc_pos + 1);
        siglum.erase(eoc_pos, std::string::npos);
    } else {
        //TODO: error message
        return;
    }

    std::size_t eob_pos = siglum.find(eob);
    if(eob_pos != std::string::npos) {
        chapter = siglum.substr(eob_pos + 1);
        siglum.erase(eob_pos, std::string::npos);
        book = siglum;
    }
    else {
        return;
        //TODO: error message
    }

    std::size_t eov_pos = verses.find(eov);
    if(eov_pos != std::string::npos) {
        lastVerse = verses.substr(eov_pos + 1);
        lastVerseNum = stoi(lastVerse);
        verses.erase(eov_pos, std::string::npos);
    } else {
        return;
        //TODO: error message*
    }

    BOOK = book;
    CHAPTER = chapter;
    FIRSTVERSE = verses;
    LASTVERSE = lastVerseNum;
}

void readContentFromFile(const std::string& book, const std::string& chapter, const std::string& firstVerse, int lastVerse) {
    int i = 0;

    std::ifstream file;
    file.open("Biblia.txt");
    if(!file.is_open()) {
        return;
    }

    std::string firstLine = bookName(book) + " " + chapter + " " + firstVerse;
    std::string line;

    while(file) {
        bool found;
        std::getline(file, line);
        found = line.find(firstLine) != std::string::npos;
        if(i < lastVerse && found) {
            std::cout << line << std::endl;
            i++;
        }
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "nkbr: bad usage \n";
        return 1;
    }
    siglumParser(argv[1]);
    readContentFromFile(BOOK, CHAPTER, FIRSTVERSE, LASTVERSE);
}
