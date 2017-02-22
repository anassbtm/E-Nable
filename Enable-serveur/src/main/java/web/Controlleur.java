package web ;

import java.io.IOException;

import javax.servlet.http.HttpServletResponse;
import javax.websocket.OnError;
import javax.websocket.OnMessage;
import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;

import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
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
		}
	

	@RequestMapping(value = "/set/{numDoigt1}/{numDoigt2}/{numDoigt3}/{numDoigt4}", method = RequestMethod.PUT)
	@ResponseStatus(HttpStatus.OK)
	@ResponseBody
	public void setInfoDoigt(HttpServletResponse r, @PathVariable("numDoigt1") boolean numDoigt1, 
			@PathVariable("numDoigt2") boolean numDoigt2, @PathVariable("numDoigt3") boolean numDoigt3,
			@PathVariable("numDoigt4") boolean numDoigt4)
	{
		
		doigts[0] = numDoigt1 ;
		doigts[1] = numDoigt2 ;
		doigts[2] = numDoigt3 ;
		doigts[3] = numDoigt4 ;
		System.out.println("Modification etat doigts");
	}

	@OnMessage
    public void getState(Session session, String msg, boolean last)
    {
        try 
        {
            while (session.isOpen())
            {   
            	session.getBasicRemote().sendText(doigts[0]+" "+doigts[1]+" "+doigts[2]+" "+doigts[3]);
            	
            	Thread.sleep(100);
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