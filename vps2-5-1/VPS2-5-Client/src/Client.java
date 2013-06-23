import java.io.*;
import java.net.*;


class Client {
	public static void main( String args [ ] ) throws Exception {
		String sentence , modSentence;
		BufferedReader inFromUser = new BufferedReader (new InputStreamReader (System. in ) ) ;
		Socket clientSocket1 = new Socket ( Inet4Address.getLocalHost() , 6789);
		Socket clientSocket2 = new Socket ( Inet4Address.getLocalHost() , 6789);
		DataOutputStream outToServer1 = new DataOutputStream ( clientSocket1 . getOutputStream ( ) ) ;
		DataOutputStream outToServer2 = new DataOutputStream ( clientSocket2 . getOutputStream ( ) ) ;
		BufferedReader inFromServer1 = new BufferedReader (new InputStreamReader ( clientSocket1 . getInputStream ( ) ) ) ;
		BufferedReader inFromServer2 = new BufferedReader (new InputStreamReader ( clientSocket2 . getInputStream ( ) ) ) ;
		sentence = inFromUser . readLine ( ) ;
		System. out . println ("writing via socket 1 (without endline)\n");
		outToServer1.writeBytes(sentence);
		System. out . println ("writing via socket 2 (with endline)\n");
		outToServer2.writeBytes(sentence + '\n');
		modSentence = inFromServer2 . readLine ( ) ;
		System. out . println ( "From Socket 2: " + modSentence );
		System. out . println ("writing endline to socket 1\n");
		outToServer1.writeBytes("\n");
		//Wait for Bye
		modSentence = inFromServer1 . readLine ( ) ;
		System. out . println ( "From Socket 1: " + modSentence );
		clientSocket1 . close ( ) ;
		clientSocket2 . close ( ) ;
	}
}
