#include <iostream>
#include <string>
#include <vector>

// Genere un hash en se basant sur l'index, la data et le precedent hash du block
std::string genererHash(int index, std::string data, std::string precedentHash)
{
	std::string input = std::to_string(index) + data + precedentHash;
	std::hash<std::string> hasher;
	return std::to_string(hasher(input));
}

class Block
{
public:
    int index;
    std::string data;
    std::string precedentHash;
    std::string hash;

    Block(int index, std::string data, std::string precedentHash):
        index(index), 
        data(data), 
        precedentHash(precedentHash)
        {
            hash = genererHash(index, data, precedentHash);
        }

    // Fonction pour vérifier l'intégrité du bloc
    void verifierIntegriteBlock() {
        std::string calculatedHash = genererHash(index, data, precedentHash);
		bool integrite = calculatedHash == hash;
		std::cout << "Integrite du bloc numero " << index << " : " << integrite << std::endl;
    }
};

class Blockchain
{
public:
    std::vector<Block> chain;

    Blockchain()
    {
		// Création du bloc génésis / premier block de la blockchain
        Block genesisBlock(0, "Genesis Block", "0");
        chain.push_back(genesisBlock);
    }

    // Fonction pour afficher un bloc
    void ajouterBlock(std::string data)
    {
		Block precedentBlock = chain.back();
        Block newBlock(precedentBlock.index + 1, data, precedentBlock.hash);
        chain.push_back(newBlock);
    }

    // Fonction pour afficher la blockchain
    void afficherBlockchain()
    {
        for (Block block : chain)
        {
            std::cout << "------------------------" << std::endl;
            std::cout << "Index: " << block.index << std::endl;
            std::cout << "Donnees: " << block.data << std::endl;
            std::cout << "Hash precedent: " << block.precedentHash << std::endl;
            std::cout << "Hash: " << block.hash << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }

    // Fonction pour afficher un bloc singulier
	void afficherBlock(int index)
	{
		Block block = chain[index];
		std::cout << "------------------------" << std::endl;
		std::cout << "Index: " << block.index << std::endl;
		std::cout << "Donnees: " << block.data << std::endl;
		std::cout << "Hash precedent: " << block.precedentHash << std::endl;
		std::cout << "Hash: " << block.hash << std::endl;
		std::cout << "------------------------" << std::endl;
	}

    // Fonction pour vérifier l'integrite de la chaine
    void verifierIntegriteChaine()
    {
        bool integrite = true;

        for (int i = 1; i < chain.size(); ++i)
        {
            Block blockCourant = chain[i];
            Block precedentBlock = chain[i - 1];

            if (blockCourant.hash != genererHash(blockCourant.index, blockCourant.data, blockCourant.precedentHash))
            {
                integrite = false;
            }

            if (blockCourant.precedentHash != precedentBlock.hash)
            {
                integrite = false;
            }
        }

        std::cout << "Integrite de la blockchain : " << integrite << std::endl;
    }
};

int main()
{
    Blockchain maBlockchain;
    maBlockchain.ajouterBlock("Bloc 1");
    maBlockchain.ajouterBlock("Bloc 2");
    maBlockchain.ajouterBlock("Bloc 3");
    maBlockchain.afficherBlockchain();
	maBlockchain.chain[1].verifierIntegriteBlock();
	maBlockchain.verifierIntegriteChaine();

    // Test avec modification d'une data
	maBlockchain.chain[1].data = "Bloc 1 modifie";
	maBlockchain.afficherBlock(1);
	maBlockchain.chain[1].verifierIntegriteBlock();
	maBlockchain.verifierIntegriteChaine();
}
