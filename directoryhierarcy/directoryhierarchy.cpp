/* Hakemistorakenne
 *
 * Kuvaus:
 * Käynnistettäessä ohjelma lukee tiedoston, joka sisältää tiedot
 * erilaisista hakemistoista ja niiden hierarkiasta. Hakemisto-
 * rakenteessa käyttäjän on mahdollista tulostaa työhakemiston
 * polku, muuttaa työhakemistoa ja hakea erilaisia tietoja
 * hakemiston rakenteesta ja ominaisuuksista käyttöliittymän
 * avulla erilaisilla komennoilla.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Ohjelmassa hakemistorakenne on toteutettu vektorin avulla,
 * johon tallennetaan osoittimet eri hakemistoista. Työhakemisto
 * on muodostettu myös osoittimen avulla. Lisäksi ohjelmaan on
 * luotu useampia apufunktioita helpottamaan ja selkeyttämään
 * ohjelmakoodin toteutusta.
 *
 * */

#include "directoryhierarchy.hh"
#include <map>

DirectoryHierarchy::DirectoryHierarchy() {}

DirectoryHierarchy::~DirectoryHierarchy() {

    // Käy läpi kaikki moduulin muuttujat ja tuhoaa ne.

    while (data_.size() != 0) {
        Directory* part = data_.back();
        data_.pop_back();
        delete part;

    }
}

bool DirectoryHierarchy::findDirectory(const std::string &id) {

    // Käy läpi koko datan ja tutkii, löytyykö kyseinen id ja palauttaa
    // sen mukaan totuusarvon.
    for (auto ids : data_) {
        if (id == ids->id_) {
            return true;
        }
    }
    return false;
}

Directory* DirectoryHierarchy::getPointer(const std::string &id) const {

    Directory* ptr = nullptr;

    // Käy läpi datan ja etsii id:tä vastaavan osoittimen.
    for (auto ids : data_) {
        if (ids->id_ == id) {
            ptr = ids;
            break;
        }
    }

    // Palauttaa osoittimen arvon.
    return ptr;
}

void DirectoryHierarchy::addNewDirectory(const std::string &id,
                                         const std::string &timestamp,
                                         int size, std::ostream &output) {

    // Tutkii, onko hakemisto jo lisätty.
    if (findDirectory(id) == true) {
        output << "Error. Directory already added." << std::endl;

    } else {

        // Luo uuden hakemiston ja lisää sen tietorakenteeseen.
        Directory* new_direc = new Directory{id, timestamp, size,
                nullptr, {}};
        data_.push_back(new_direc);
    }
}

void DirectoryHierarchy::addRelation(const std::string &directory,
                                     const std::string &parent,
                                     std::ostream &output) {

    // Tutkii, löytyykö annettu hakemisto tietorakenteesta.
    if (findDirectory(directory) == false) {
        output << "Error. "<< directory << " not found." << std::endl;

    } else if (parent == "") {

        // Jos ylähakemisto on "", niin lisätään ylähakemistoksi nullptr
        // ja lisätään hakemisto kotihakemistovektoriin.
        Directory* current = getPointer(directory);
        current->parent_ = nullptr;
        home_dictionaries_.push_back(current);

    } else if (findDirectory(parent) == false) {

        // Jos ylähakemistoa ei ole tietorakenteessa, tulostetaan
        // error viesti.
        output << "Error. "<< parent << " not found." << std::endl;
    } else {

        // Siirretään ylähakemisto-osoitin osoittamaan hakemiston ylä-
        // hakemistoa.
        Directory* current = getPointer(directory);
        current->parent_ = getPointer(parent);

        // Lisätään myös itse hakemisto ylähakemiston alahakemistoksi.
        current->parent_ ->subdirectories_.push_back(current);

    }
}

void DirectoryHierarchy::commandPrintWorkingDirectory(std::ostream &output)
const {

    // Luodaan vektori, johon sisällytetään polun sisältämät hakemistot.
    std::vector<std::string> links = {};

    // Haetaan työhakemiston osoitin ja luodaan string avuksi.
    Directory* path = current_;
    std::string help_text = "";

    // Käydään läpi koko hakemiston polku siirtymällä aina seuraavaan
    // ylähakemistoon, kunnes ollaan aivan ylhäällä.
    while (path != nullptr) {
        links.push_back(path->id_);
        path = path->parent_;
    }

    // Lisätään home alkuun.
    links.push_back("home");

    // Käydään läpi polku vektorista väärinpäin, jotta saadaan polku aikaiseksi
    // oikeaan suuntaan ja tallennetaan polku string apumuuttujaan.
    for (int k = links.size()-1; k >= 0; --k) {
        help_text += "/";
        help_text += links[k];
    }

    // Annetaan outputtina polku
    output << help_text << std::endl;
}

void DirectoryHierarchy::commandList(std::ostream &output) const {

    // Luodaan set, johon tallennetaan alihakemistot.
    std::set<std::string> subs = {};

    // Hakeee alihakemistoiksi kotihakemistot, jos ollaan aivan ylhäällä
    // hakemistorakenteessa.
    if (current_ == nullptr) {
        for (Directory* dict : home_dictionaries_) {
            subs.insert(dict->id_);
        }

    } else {

        // Hakee nykysen työhakemiston alihakemistot ja tallentaa ne settiin.
        for (Directory* dict : current_->subdirectories_) {
            subs.insert(dict->id_);
        }
    }

    // Käy läpi setin ja tulostaa halutun tulostuksen.
    for (std::string part : subs) {
        Directory* help_ptr = getPointer(part);

        output << part << ", " << help_ptr->timestamp_ << ", " <<
                  help_ptr->size_ << std::endl;
    }

}

int DirectoryHierarchy::CalculateSum(const Directory* id) const{

    // Luo vektorin alihakemistoista ja muodostaa muuttujan sum, johon
    // tallennetaan summa alihakemistojen koosta.
    std::vector<Directory*> dicts = id->subdirectories_;
    int sum = 0;

    if (dicts.empty()) {
        return sum;

    } else {

        // Käy läpi alihakemistot ja lisää niiden koot summaan.
        // Lisäksi laskee alihakemistojen alihakemistoille koot ja
        // talletaa ne samaan muuttujaan.
        for (auto item : dicts) {
            sum += item->size_;
            sum += CalculateSum(item);

        }
        return sum;
    }
}

void DirectoryHierarchy::commandDiskUsage(std::ostream &output) const {

    // Luo mapin, johon tallennetaan alihakemistojen tiedot.
    std::map<std::string,int> info = {};

    // Jos ollaan ylhäällä, käydään läpi kotihakemistot.
    if (current_ == nullptr) {
        for (Directory* sub : home_dictionaries_) {

            // Lasketaan muuttujaan x hakemiston ja sen alihakemistojen kokojen
            // summa.
            int x = CalculateSum(sub);
            x += sub->size_;

            // Lisätään tiedot mappiin.
            info.insert({sub->id_,x});
        }
    } else {

        // Käydään läpi alihakemistot.
        for (Directory* sub : current_->subdirectories_) {

            // Lasketaan muuttujaan x hakemiston ja sen alihakemistojen kokojen
            // summa.
            int x = CalculateSum(sub);
            x += sub->size_;

            info.insert({sub->id_,x});
        }
    }

    // Käydään läpi map ja tulostetaan halutut tiedot halutussa muodossa.
    for (auto part : info) {
        output << part.second << " /" << part.first << std::endl;
    }
}

void DirectoryHierarchy::commandChangeDirectory(const std::string &id,
                                                std::ostream &output) {

    if (current_ == nullptr) {
        // Apumuuttuja, jonka avulla katsotaan löytyykö id tietorakenteesta.
        int n = 0;

        // Jos ollaan aivan ylhäällä, käydään läpi kotihakemistot.
        for (auto home_dict : home_dictionaries_) {

            // Tutkitaan löytyykö id kotihakemistoista.
            if (id == home_dict->id_) {

                // Jos id löytyy siirretään haluttuun hakemistoon.
                current_ = home_dict;
                ++n;
                break;
            } else {

            }
        }

        // Tutkitaan muutamaa eri virhetilannetta.
        if (id == "..") {
            output << "Error. Already at the root."  << std::endl;
        } else if (n == 0) {
            output << "Error. " << id << " not found."  << std::endl;
        } else {}

    } else {

        bool subdirectory = false;
        for (auto sub : current_->subdirectories_) {
            if (id == sub->id_) {
                subdirectory = true;
                break;
            }
        }

        if (id == "~") {
            current_ = nullptr;
        } else if (id == "..") {
            current_ = current_->parent_;
        } else if (subdirectory == true) {
            current_ = getPointer(id);
        } else {
            output << "Error. " << id <<" not found."<< std::endl;
        }
    }
}

void DirectoryHierarchy::helpFind(std::set<std::string> &v,Directory* id,
                                  std::string start_text, int n) const{
    --n;
    std::string test = "";

    if (n == 0) {

    } else if (id->subdirectories_.empty() == true) {

    } else {

        // Jos n != 0 ja id:llä on alihakemistoja, käydään läpi alihakemistot
        // ja luodaan tekstinä polku, joka lisätään settiin.
        for (auto sub : id->subdirectories_) {

            test = start_text + "/" + sub->id_;
            v.insert(test);

            // Käydään läpi myös alihakemiston alihakemistot.
            helpFind(v,sub,test,n);
        }
    }
}

void DirectoryHierarchy::commandFind(const std::string &id, const int n,
                                     std::ostream &output) const {

    // Tutkitaan apumuuttuja k:n avulla, löytyykö id tietorakenteeta.
    int k = 0;

    // Käydään läpi kotihakemistot, jos ollaan ihan ylhäällä.
    if (current_ == nullptr) {
        for (auto part : home_dictionaries_) {
            if (part->id_ == id) {
                ++k;
            }
        }
    } else {
        for (auto part : current_->subdirectories_) {
            if (part->id_ == id) {
                ++k;
            }
        }
    }



    if (n < 1) {
        output << "Error. Level can't be less than 1." << std::endl;

    } else if (k == 0) {
        output << "Error. " << id << " not found." << std::endl;

    } else {

        // Jos n < 1 ja hakemisto löytyi, haetaan osoitin id:lle ja luodaan
        // apuset.
        Directory* ptr = getPointer(id);
        std::set<std::string> texts = {};

        if (ptr->subdirectories_.empty() == false) {

            // Luodaan apumuuttuja, johon tallennetaan teksti.
            std::string help = "";

            // Käydään läpi alihakemistot ja luodaan niille polku tekstinä.
            // Lisätään polku settiin ja haetaan alihakemiston alihakemistoille
            // myös polut.
            for (auto subs : ptr->subdirectories_) {
                help += ptr->id_ + "/" + subs->id_;
                texts.insert(help);
                helpFind(texts, subs, help, n);

                help = "";
            }

            // Käydään läpi set ja tulostetaan outputtiin tulostus.
            for (auto line : texts) {
                output << line << std::endl;
            }
            }
        }
    }

void DirectoryHierarchy::checkTime(const std::string id,
                                   std::set<std::string> &v, std::string time,
                                   std::string asked_id) const {

    // Haetaan id:lle osoitin.
    Directory* pointer = getPointer(id);

    if (pointer->subdirectories_.empty() != true) {

        // Käydään läpi hakemiston alihakemistot.
        for (auto sub : pointer->subdirectories_) {
            if (sub->timestamp_ == time) {

                if (sub->id_ != asked_id) {
                    v.insert(sub->id_);
                }

                checkTime(sub->id_,v,time, asked_id);
            }
        }
    }
}

void DirectoryHierarchy::commandAsOldAs(const std::string &id,
                                        std::ostream &output) const {

    // Haetaan id:lle osoitin ja luodaan setti, jonne tallennetaan
    // tulostettavat hakemistot.
    Directory* help_ptr = getPointer(id);
    std::string time = help_ptr->timestamp_;
    std::set<std::string> v = {};
    Directory* ptr_path = help_ptr;

    // Käydään läpi tietorakennetta ja etsitään ylin saman ajan hakemisto.
    while (ptr_path != nullptr) {

        if (ptr_path->parent_ == nullptr) {
            break;
        } else if (ptr_path->timestamp_ == time) {
            if (ptr_path->parent_->timestamp_ == time) {
                ptr_path = ptr_path->parent_;

            } else {
                break;
            }
        } else {
            break;
        }
    }


    // Käydään läpi ylimmän saman ajan hakemiston alihakemistot.
    for (auto dicts : ptr_path->subdirectories_) {

        // Lisätään settiin, jos aika on sama, eikä hakemisto komennon hakemisto.
        if (dicts->timestamp_ == time and dicts->id_!= id) {
            v.insert(dicts->id_);
        }

        // Haetaan myös alihakemistot vastaavasti, joilla sama aika.
        checkTime(dicts->id_,v,time,id);
    }

    // Lisätään myös ylin saman aikaleiman hakemisto, jos se ei ole
    // sama, kuin haettu hakemisto.
    if (ptr_path->id_ != id) {
        v.insert(ptr_path->id_);
    }

    // Tulostetaan etsityt hakemistot.
    for (auto dict : v) {
        output << dict << std::endl;

    }
}

void DirectoryHierarchy::getSizes(const std::string id, std::vector<int> &v,
                                  std::set<std::string,
                                  std::string> &info) const {

    // Haetaan id:lle osoitin.
    Directory* ptr = getPointer(id);
    // Tallennetaan hakemiston koko.
    v.push_back(ptr->size_);

    // Käydään läpi hakemiston alihakemistot ja tallennetaan niiden koot ja
    // haetaan vastaavasti myös niiden alihakemistoille koot.
    for (auto sub : ptr->subdirectories_) {
        v.push_back(sub->size_);

        getSizes(sub->id_,v, info);
    }


}

void DirectoryHierarchy::getDictBySize(const std::string id, const int size,
                                       std::string &name) const {
    Directory* ptr = getPointer(id);

    // Jos hakemiston koko vastaa haluttua kokoa, tallennetaan se muuttujaan
    // name.
    if (ptr->size_ == size) {
        name = ptr->id_;
    }

    // Käydään läpi hakemiston alihakemistoja.
    for (auto sub : ptr->subdirectories_) {

        // Jos alihakemiston koko täsmää, tallennetaan se muuttujaan name.
        if (sub->size_ == size) {
            name = sub->id_;

        }
        // Tutkitaan myös alihakemistojen alihakemistot.
        getDictBySize(sub->id_, size, name);
    }
}

void DirectoryHierarchy::commandGreatest(const std::string &id,
                                         std::ostream &output) const {

    // Luodaan vektori, johon tallennetaan koot vertailtaviksi sekä set
    // tietorakenne, johon tallennetaan hakemistojen koot ja nimet
    std::vector<int> v = {};
    std::set<std::string, std::string> info = {};

    // Haetaan hakemiston ja alihakemistojen koot.
    getSizes(id,v, info);

    // Määritetään maksimikoko ja muuttuja, johon tallennetaan etsityn
    // hakemiston nimi.
    int max_size = 0;
    std::string name = "";

    // Käydään läpi kokoja ja etsitään niistä suurin.
    for (auto num : v) {
        if (max_size < num) {
            max_size = num;
        }
    }

    // Haetaan löydettyä kokoa vastaava hakemisto.
    getDictBySize(id, max_size, name);

    // Tulostetaan haluttu tulostus.
    if (id == name) {
        output << id << " ( " << max_size << " )  is the greatest subdirectory "
                "in its subdirectories." << std::endl;

    } else {
        output << name << " ( " << max_size << " )  is the greatest subdirectory"
                " in " << id << "'s subdirectories." << std::endl;
    }

}

void DirectoryHierarchy::commandSmallest(const std::string &id,
                                         std::ostream &output) const {

    // Luodaan vektori, johon tallennetaan koot vertailtaviksi sekä set
    // tietorakenne, johon tallennetaan hakemistojen koot ja nimet
    std::vector<int> v = {};
    std::set<std::string, std::string> info = {};

    getSizes(id,v, info);

    int min_size = 0;
    std::string name = "";
    int n = 0;

    // Käydään läpi hakemistojen koot ja etsitään pienin arvo.
    for (auto num : v) {

        // Määritellään ensimmäisellä kerralla minimiarvoksi suoraan
        // hakemiston koko.
        if (n == 0) {
            min_size = num;
            ++n;

        } else {
            if (min_size > num) {
                min_size = num;
            }
        }
    }

    // Haetaan löydettyä kokoa vastaava hakemisto.
    getDictBySize(id, min_size, name);

    // Tulostetaan haluttu tulostus.
    if (id == name) {
        output << id << " ( " << min_size << " )  is the smallest subdirectory"
                    " in its subdirectories." << std::endl;
    } else {
        output << name << " ( " << min_size << " )  is the smallest subdirectory"
                    " in " << id << "'s subdirectories." << std::endl;
    }




}

