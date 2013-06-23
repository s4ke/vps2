import java.io.*;
import java.net.*;
class Server {
	public static void main( String args [ ] ) throws Exception {
		Worker latestW = null;
		ServerSocket welcomeSocket = new ServerSocket (6789);
		// Warten auf Verbindungsanfragen " uber Port 6789
		for ( ; ; ) {
			Socket commSocket = welcomeSocket . accept ( ) ;
			latestW = new Worker(commSocket);
			latestW.start();
		}
	}
}