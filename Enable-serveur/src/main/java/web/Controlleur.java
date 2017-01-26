package web ;

import javax.websocket.server.ServerEndpoint;

import org.springframework.stereotype.Controller;


@ServerEndpoint("/majTime")
@Controller
public class Controlleur implements Service
{	

	public Controlleur() 
	{
		
	}
}