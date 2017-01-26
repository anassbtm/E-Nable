package tests;

import org.junit.runner.RunWith;
import org.springframework.mock.web.MockHttpServletRequest;
import org.springframework.mock.web.MockHttpServletResponse;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import web.Controlleur;

//@ContextConfiguration(locations = {"classpath:/application-context.xml"})
@ContextConfiguration
({
	"file:src/main/webapp/WEB-INF/do-servlet.xml",
	"file:src/main/webapp/WEB-INF/web.xml",
})
@RunWith(SpringJUnit4ClassRunner.class)
public class Tests
{
	private Controlleur c ;
	private MockHttpServletRequest request;
    private MockHttpServletResponse response;
  
}
