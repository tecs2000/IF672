#include <bits/stdc++.h>
using namespace std;

struct NodeList {
    int valor;
    NodeList *next = NULL;
};

struct Posto{
    NodeList* head = NULL;

    void insert(int id){
        NodeList *ptr = new NodeList();
        ptr->valor = id;
        ptr->next = head;
        head = ptr;
    }
    bool search(int id){
        NodeList *current = head;
        while(current != NULL){
            if(current->valor == id) return true;
            else current = current->next;
        }
        return false;
    }
    void remove(int v){
        if(search(v) == true){
            NodeList* temp = head;
            NodeList* prev = NULL;

            if (temp != NULL && temp->valor == v)
            {
                head = temp->next;
                return;
            }
            while (temp != NULL && temp->valor != v)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next;
        }
    }
    bool isEmpty(){
        if(head == NULL) return true;
        else return false;
    }
};

struct NodeTree{
    int casta;
    Posto posto;
    NodeTree* left;
    NodeTree* right;
};

struct Tree{
    NodeTree* root = NULL;

    NodeTree* newNode(int casta, int id){
        NodeTree *temp = new NodeTree();
        temp->casta = casta;
        temp->left = temp->right = NULL;
        temp->posto.insert(id);
        return temp;
    };
    NodeTree* insertNode(NodeTree* root, int casta, int id){
        if(root == NULL) return newNode(casta, id);
        else if(casta < root->casta) root->left = insertNode(root->left, casta, id);
        else root->right = insertNode(root->right, casta, id);

        return root;
    };
    NodeTree* search(NodeTree* root, int casta)
    {
        if (root == NULL || root->casta == casta)
            return root;

        if (root->casta < casta)
            return search(root->right, casta);

        return search(root->left, casta);
    }
    int getHeight(NodeTree *node, int data, int level)
    {
        if (node == NULL)
            return 0;

        if (node->casta == data)
            return level;

        int downlevel = getHeight(node -> left, data, level + 1);
        if (downlevel != 0)
            return downlevel;

        downlevel = getHeight(node->right, data, level + 1);
        return downlevel;
    }

    int maxDepth(NodeTree* node)
    {
        if (node == NULL)
            return 0;
        else
        {
            int lDepth = maxDepth(node->left);
            int rDepth = maxDepth(node->right);

            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }

    NodeTree * minValueNode(NodeTree* node)
    {
        NodeTree* current = node;
        while (current && current->left != NULL)
            current = current->left;

        return current;
    }

    NodeTree* deleteNode(NodeTree* root, int key)
    {
        if (root == NULL) return root;

        if (key < root->casta)
            root->left = deleteNode(root->left, key);

        else if (key > root->casta)
            root->right = deleteNode(root->right, key);

        else
        {
            if (root->left == NULL)
            {
                NodeTree *temp = root->right;
                free(root);
                return temp;
            }
            else if (root->right == NULL)
            {
                NodeTree *temp = root->left;
                free(root);
                return temp;
            }

            NodeTree* temp = minValueNode(root->right);

            root->casta = temp->casta;
            root->posto = temp->posto;

            root->right = deleteNode(root->right, temp->casta);
        }
        return root;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, h, f;
    cin >> n >> h >> f;

    Tree* bases[n];
    for(int i = 0 ; i < n; i++) bases[i] = new Tree();

    string comando;
    cin >> comando;

    while(comando != "END"){

        int c, id, b;
        cin >> c >> id >> b;

        if(comando == "ADM" || comando == "INF"){
            NodeTree* temp = bases[b]->root;
            NodeTree* aux = bases[b]->search(temp, c);

            int contador = 0;
            if(aux == NULL){
                bases[b]->root = bases[b]->insertNode(temp, c, id);

                if(bases[b]->maxDepth(temp) > h) {  //Checa se passou o limite de altura
                    while(contador < n) {
                        bases[(b+contador)%n]->deleteNode(temp, c);
                        contador++;

                        temp = bases[(b+contador)%n]->root;

                        aux = bases[b]->search(temp, c);
                        if(aux == NULL) {
                            temp = bases[(b+contador)%n]->insertNode(temp, c, id);
                            if(bases[(b+contador)%n]->maxDepth(temp) <= h)
                                break;
                        } else{
                            aux->posto.insert(id);
                            break;
                        }
                    }
                }
            }
            else
                aux->posto.insert(id);

            if(comando == "INF") {
                if(contador > n) cout << -1 << endl;
                else cout << (b+contador)%n << endl;
            }
        }
        else if(comando == "SCH" || comando == "EXT"){
            NodeTree* temp = bases[b]->search(bases[b]->root, c);

            if(temp != NULL){
                if(temp->posto.search(id)){
                    if(comando == "SCH")
                        cout << bases[b]->getHeight(bases[b]->root, c, 0) << endl;
                    else {
                        temp->posto.remove(id);
                        if(temp->posto.isEmpty())
                            bases[b]->deleteNode(bases[b]->root, c);
                    }
                }
                else if (comando == "SCH")
                    cout << -1 << endl;
            }
            else if(comando == "SCH")
                cout << -1 << endl;
        }
        cin >> comando;
    }
}
