using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MvcApplication3.Controllers
{
    public class HelloWorldController : Controller
    {
        //
        // GET: /HelloWorld/

 
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Welcome(string name, int numTimes = 4)
        {
            ViewBag.Message = "Hello Scott" + name;
            ViewBag.NumTimes = numTimes;

            return View();
        }
    }
}
