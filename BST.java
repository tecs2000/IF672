import java.util.Scanner;

public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int qtd_bases, h_max, qtd_inicial;

		qtd_bases = in.nextInt();
		h_max = in.nextInt();
		qtd_inicial = in.nextInt();

		BinaryTree bases[] = new BinaryTree[qtd_bases];
		for(int i = 0; i < qtd_bases; i++) bases[i] = new BinaryTree();

		String comando;
		int casta, id, base;

		boolean stop = false;
		
		while(!stop) {
			comando = in.next();
			
			if(!comando.equals("END")) {
				casta = in.nextInt();
				id = in.nextInt();
				base = in.nextInt();

				Node temp = bases[base].root;

				if (comando.equals("INF") || comando.equals("ADM")) {

					int contador = 0;
					bases[base].insert(casta, id);

					if(bases[base].getDepthTree(temp) > h_max) {  //Checa se passou o limite de altura

						while(contador < qtd_bases) {
							bases[(base+contador)%qtd_bases].remove(temp, casta);
							contador++;

							temp = bases[(base+contador)%qtd_bases].root;

							bases[(base+contador)%qtd_bases].insert(casta, id);

							if(bases[(base+contador)%qtd_bases].getDepthTree(temp) <= h_max) break;						
						}
					}
					if(comando.equals("INF")) {
						if(contador>qtd_bases) System.out.println("-1");
						else System.out.println((base+contador)%qtd_bases);
					}
				} else if (comando.equals("EXT")) {
					bases[base].EXT(temp, casta, id);

				} else {
					System.out.println(bases[base].SCH(temp, casta, id));
				}	
			}
			else stop = true;
		}
	}
}		

class Postos {
	private int id;
	private Postos next;

	public Postos() {
		this.id = -1;
		this.next = null;
	}

	public void inserir(int id) {
		if (this.id == -1) {
			this.id = id;
			this.next = new Postos();
		} else {
			this.next.inserir(id);
		}
	}

	public boolean remover(int id) {
		if (this.id != -1) {
			if (this.id == id) {
				this.id = -2;
				return true;
			} else {
				return this.next.remover(id);
			}
		} else {
			return false;
		}
	}

	public boolean search(int id) {
		if (this.id != -1) {
			if (this.id == id) {
				return true;
			} else {
				return this.next.search(id);
			}
		} else {
			return false;
		}
	}

	public boolean isempty() { // checa se a remocao extinguiu o posto
		if (this.id != -1) {
			if (this.id == -2) {
				return this.next.isempty();
			} else {
				return false;
			}
		} else {
			return true;
		}
	}
}

class Node {
	int casta;
	Postos postos;
	Node left, right;

	public Node(int casta) {
		this.casta = casta;
		this.postos = new Postos();
		this.left = this.right = null;
	}
}

class BinaryTree {
	Node root;

	void insert(int casta, int id) { 
		root = insertRec(root, casta, id); 
	}
	public Node insertRec(Node root, int casta, int id) {
		if (root == null) { 
			root = new Node(casta);
			root.postos.inserir(id);
			return root; 
		} 	 
		if (casta < root.casta) 
			root.left = insertRec(root.left, casta, id); 
		else if (casta > root.casta) 
			root.right = insertRec(root.right, casta, id);
		else			//Achou a casta
			root.postos.inserir(id);
		return root; 
	}

	public void EXT(Node root, int casta, int id) {
		if (root != null) {
			if (root.casta == casta) { 		// Achou a casta de insercao
				root.postos.remover(id);
				if(root.postos.isempty()) {
					this.root = remove(this.root, casta);
				}
			} else if (casta > root.casta)
				EXT(root.right, casta, id);

			else
				EXT(root.left, casta, id);
		}
	}

	public int minCasta(Node root) {
		if (root.left == null)
			return root.casta;
		else
			return minCasta(root.left);
	}

	public Postos minPosto(Node root) {
		if (root.left == null)
			return root.postos;
		else
			return minPosto(root.left);
	}

	public Node remove(Node root, int casta) 
	{ 
		if (root == null)  return root; 
		if (casta < root.casta) 
			root.left = remove(root.left, casta); 
		else if (casta > root.casta) 
			root.right = remove(root.right, casta); 
		else
		{ 
			if (root.left == null) 
				return root.right; 
			else if (root.right == null) 
				return root.left; 
			else
				root.casta = minCasta(root.right);
			root.postos = minPosto(root.right);
			root.right = remove(root.right, root.casta); 
		} 
		return root; 
	}

	public int getDepthNode(Node root, int casta, int level) {
		if (root == null)
			return 0;

		if (root.casta == casta)
			return level;

		int downlevel = getDepthNode(root.left, casta, level + 1);
		if (downlevel != 0)
			return downlevel;

		else downlevel = getDepthNode(root.right, casta, level + 1);
		return downlevel;
	}

	public int SCH(Node root, int casta, int id) {
		if (root != null) {
			if (root.casta == casta) { 		// Achou a casta

				if (root.postos.search(id)) 
					return getDepthNode(this.root, casta, 0);
				else
					return -1;

			} else if (casta > root.casta)
				return SCH(root.right, casta, id);
			else
				return SCH(root.left, casta, id);
		} else
			return -1;
	}

	public int getDepthTree(Node root) {
		if (root == null)
			return 0;
		else {
			int lDepth = getDepthTree(root.left);
			int rDepth = getDepthTree(root.right);

			if (lDepth > rDepth)
				return (lDepth + 1);
			else
				return (rDepth + 1);
		}
	}
}
