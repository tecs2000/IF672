import java.util.HashMap;
import java.util.Scanner;

public class Lista6{

	static int[][][] cubo;
	static int[][][] memo;
	static int fx, fy, fz, m, n, s;

	public static int calculator(int x, int y, int z, int auxX, int auxY, int auxZ) {		
		if(memo[x][y][z] != 0) return memo[x][y][z];
		if(x == fx && y == fy && z == fz) return cubo[x][y][z];
		
		else {
			if(x > fx) 
				auxX = cubo[x][y][z] + calculator(x-1, y, z, auxX, auxY, auxZ);
			
			if(y < fy) 
				auxY = cubo[x][y][z] + calculator(x, y+1, z, auxX, auxY, auxZ);
			
			if(z < fz) 
				auxZ = cubo[x][y][z]  + calculator(x, y, z+1, auxX, auxY, auxZ);
			
			int a = Math.max(auxX, auxY);
			int b = Math.max(a, auxZ);
			memo[x][y][z] = b;
			return b;
		}
	}

	public static void main(String [] args) {
		Scanner in = new Scanner(System.in);

		m = in.nextInt();    //dimensao x do cubo
		n = in.nextInt();    //dimensao y do cubo
		s = in.nextInt();    //dimensao z do cubo

		fx = in.nextInt();   //coordenada x do ponto final 
		fy = in.nextInt();   //coordenada y do ponto final
		fz = in.nextInt();   //coordenada z do ponto final

		cubo = new int[m][n][s];
		memo = new int[m][n][s];

		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < s; k++)
					cubo[i][j][k] = in.nextInt();

		int p = in.nextInt();     //qtd jogadores
		for(int i = 0; i < p; i++) {
			int ix = in.nextInt(), iy = in.nextInt(), iz = in.nextInt();
			System.out.println(calculator(ix, iy, iz, 0, 0, 0));
		}
	}
}