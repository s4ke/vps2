import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.net.*;

import org.omg.CORBA_2_3.portable.OutputStream;
public class Worker extends Thread {
	static int result = 0;
	
	
	private Socket commSocket;
	
	public Worker(Socket s)
	{
		commSocket = s;
	}

	@Override
	public void run() {
		try {
			BufferedReader inFromClient;
			inFromClient = new BufferedReader (new InputStreamReader (
			commSocket. getInputStream ( ) ) );
		
			DataOutputStream outToClient = new DataOutputStream (commSocket. getOutputStream ( ) ) ;
			String clientSentence = inFromClient . readLine ( ) ;
			String capSentence = clientSentence . toUpperCase () + '\n' ;
			outToClient.writeBytes(capSentence);
			outToClient.flush();
			commSocket.close();			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	
}
