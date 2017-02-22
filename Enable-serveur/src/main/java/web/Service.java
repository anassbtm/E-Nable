package web;

import javax.servlet.http.HttpServletResponse;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;

public interface Service 
{
	@RequestMapping(value = "/set/{numDoigt1}/{numDoigt2}/{numDoigt3}/{numDoigt4}", method = RequestMethod.PUT)
	@ResponseStatus(HttpStatus.OK)
	@ResponseBody
	public void setInfoDoigt(HttpServletResponse r, @PathVariable("numDoigt1") boolean numDoigt1, 
		@PathVariable("numDoigt2") boolean numDoigt2, @PathVariable("numDoigt3") boolean numDoigt3,
		@PathVariable("numDoigt4") boolean numDoigt4);
	
}
