/* Hakemistorakenne
 *
 * Ohjelman kirjoittaja
 * Nimi: mbjeme
 *
 *
 * */


#ifndef DIRECTORYHIERARCHY_HH
#define DIRECTORYHIERARCHY_HH

#include <string>
#include <vector>
#include <set>
#include <iostream>

// Named constants to improve readability in other modules
const std::string EMPTY = "";
const int NO_SIZE = -1.0;

// Struct for a directory
struct Directory
{
    std::string id_ = EMPTY;
    std::string timestamp_ = EMPTY;
    int size_ = NO_SIZE;
    Directory* parent_ = nullptr;
    std::vector<Directory*> subdirectories_;
};

// Set of strings
using IdSet = std::set<std::string>;

/*  Class: DirectoryHierarchy
 *  Description: Datastructure for Directory-structs
 */
class DirectoryHierarchy
{
public:
    DirectoryHierarchy();
    ~DirectoryHierarchy();    

    /* Description: Adds a new directory to the datastructure.
     * Parameters:
     *  Param1: Director's ID (name) string
     *  Param2: Director's timestamp
     *  Param3: Director's size
     *  Param4: Output-stream for error-printing
     * Errormessages:
     *  If director's ID is already in datastructure:
     *      "Error. Directory already added."
     */
    void addNewDirectory(const std::string& id, const std::string& timestamp,
                         int size, std::ostream &output);

    /* Description: Adds a new directory-parentdirectory relation.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: ID of the directory's parent
     *  Param3: Output-stream for error-printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void addRelation(const std::string& directory,
                     const std::string& parent,
                     std::ostream& output);

    /* Methods implementing commands */

    /* Description: Prints the current working directory with its path.
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void commandPrintWorkingDirectory(std::ostream& output) const;

    /* Description: Prints the subdirectories of the current working directory.
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void commandList(std::ostream& output) const;

    /* Description: Prints the disk usage of the current working directory.
     * Disk usage is counted as the sum of the sizes of the current working
     * directory and all its subdirectories.
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void commandDiskUsage(std::ostream& output) const;

    /* Description: Changes the working directory to the subdirectory ID,
     * or home, or to the parent of the current working directory.
     *  Param1: ID of the directory, or "~", or "..".
     *  Param2: Output-stream for printing
     * Errormessages:
     *  If ID is not a subdirectory of the current working directory,
     *  prints the error message:
     *      "Error. <ID> not found."
     *  If the current working directory is home and if ID is "..",
     *  prints the error message:
     *      "Error. Already at the root."
     */
    void commandChangeDirectory(const std::string& id, std::ostream& output);

    /* Description: Finds the subdirectory ID of the current working directory
     * and prints all its subdirectories with their paths down to level n.
     * Parameters:
     *  Param1: ID of the subdirectory
     *  Param2: Maximum distance from the current working directory
     *  (n-1 times "hierarchy").
     *  Param3: Output-stream for printing
     * Errormessages:
     *  If ID is not a subdirectory of the current working directory,
     *  prints the error message:
     *      "Error. <ID> not found."
     *  If Param2's value is less than 1, prints the error message:
     *      "Error. Level can't be less than 1.
     */
    void commandFind(const std::string& id, const int n, std::ostream& output) const;

    /* Description: Prints all directories sharing their timestamps with the
     * given one in the same hierarchy as the given one.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: Output-stream for printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */

    void commandAsOldAs(const std::string& id, std::ostream& output) const; // VOLUNTARY

    /* Description: Prints the greatest directory in hierarchy starting
     * from the given one.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: Output-stream for printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void commandGreatest(const std::string& id, std::ostream& output) const; // VOLUNTARY

    /* Description: Prints the smallest directory in hierarchy starting
     * from the given one.
     * Parameters:
     *  Param1: ID of the directory
     *  Param2: Output-stream for printing
     * Error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     */
    void commandSmallest(const std::string& id, std::ostream& output) const; // VOLUNTARY

private:
    /* The following methods are meant to make project easier.
     * You can implement them if you want and/or create your own.
     * Anyway it would be a good idea to implement more methods
     * to make things easier and to avoid "copy-paste-coding".
     */

    // Etsii, löytyykö hakemisto jo tietorakenteesta.
    // :param id: string, etsittävä hakemisto.
    // :return: bool, kertoo löytyikö hakemisto tietorakenteesta
    bool findDirectory(const std::string& id);

    // Returns the pointer for ID.
    Directory* getPointer(const std::string& id) const;

    // Laskee alahakemistojen koot yhteen.
    // :param id: osoitin hakemistoon, jonka alahakemistojen
    // koot lasketaan yhteen.
    int CalculateSum(const Directory* id) const;

    // Etsii hakemistopolut hakemiston alahakemistoille.
    // :param v: set, johon tallennetaan löydetyt hakemistopolut
    // :param id: hakemisto, jonka alahakemiston polut etsitään
    // :param text: string, aloitusteksti alihakemiston poluille
    // :param n: int, määrä, kuinka pitkälle alihakemistoja etsitään
    void helpFind(std::set<std::string> & v, Directory* id, std::string text, int n) const;

    // Lisää oikea-aikaiset kurssit settiin talteen.
    // :param id:
    // :param v:
    // :param time:
    // :param asked_id:
    // Toiminto ja funktion commandAsOldAs toteutus kesken !
    void checkTime(const std::string id, std::set<std::string> &v, std::string time, std::string asked_id) const;

    // Tallentaa alihakemistojen koot vektoriin talteen.
    // :param id: string, hakemisto, jonka alihakemistoja käsitellään.
    // :param v: vektori, johon tallennetaaan alihakemistojen koot
    // :param info: set, johon tallennetaan alihakemistojen koot ja nimet
    void getSizes(const std::string id, std::vector<int> &v, std::set<std::string, std::string> &info) const;

    // Etsii nimen tietynkokoiselle hakemistolle.
    // :param id: string,
    void getDictBySize(const std::string id, const int size, std::string &name) const;



    // Tallennetaan current_ osoittajaan aina nykyinen kotihakemisto
    // ja parent_ osoittajaan tieto ylähakemistosta.
    Directory* parent_;
    Directory* current_ = nullptr;

    // Tallentaa data_:n sisälle kaikki osoittimet hakemistoihin ja
    // vektoriin home_dictionaries_ tallenetaan kotihakemistot.
    std::vector<Directory*> data_;
    std::vector<Directory*> home_dictionaries_;
};

#endif // DIRECTORYHIERARCHY_HH
