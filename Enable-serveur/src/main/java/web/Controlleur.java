package web ;

import java.io.IOException;

import javax.servlet.http.HttpServletResponse;
import javax.websocket.OnError;
import javax.websocket.OnMessage;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;

import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;

@ServerEndpoint("/getState")
@Controller
public class Controlleur implements Service
{	
	private static boolean[] doigts = new boolean[4];

	public Controlleur() 
	{	
		doigts = new boolean[4];
		for ( int i = 0 ; i < 4 ; i++ )
			doigts[i] = false ;
		
		doigts[0] = true ;
	}
	

	@RequestMapping(value = "/set/{numDoigt}", method = RequestMethod.PUT)
	@ResponseStatus(HttpStatus.OK)
	@ResponseBody
	public void setInfoDoigt(HttpServletResponse r, int numDoigt) 
	{
		doigts[numDoigt-1] = ! doigts[numDoigt-1] ;
	}

	
	@OnMessage
    public void getState(Session session, String msg, boolean last)
    {
        try 
        {
            while (session.isOpen())
            {   
            	session.getBasicRemote().sendText(doigts[0]+" "+doigts[1]+" "+doigts[2]+" "+doigts[3]);
            	
            	Thread.sleep(500);
            }
        } 
        catch (IOException e)
        {
            try {
                session.close();
            } 
            catch (IOException e1) { 
            	e1.printStackTrace();
            }
             e.printStackTrace();
        } catch (InterruptedException e) {
			e.printStackTrace();
		}
    }
    
    @OnError
    public void onError(Session session, Throwable thr) {
    	try 
    	{
			session.close();
		} 
    	catch (IOException e)
    	{
			e.printStackTrace();
		}
    }
}