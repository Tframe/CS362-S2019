

import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase{

	public UrlValidatorTest(String testName){
		super(tesetName);
	}
}

public void testIsValid(){








}

	//test schemes
	
	ResultPair[] schemeTest = 	{new ResultPair("http://", true),
					new ResultPair("https://", true),
					new ResultPair("ftp://", true),
					new ResultPair("mailto://", true),
					new ResultPair("file://", true),
					new ResultPair("data://", true),
					new ResultPair("irc://", true),
					new ResultPair("http", false),
					new ResultPair("http:/", false),
					new ResultPair("htp://", false),
					new ResultPair("http//", false),
					new ResultPair("://", false),
					new ResultPair("something://", false)};


	//test authority

	ResultPair[] authorityTest = 	{new ResultPair("oregonstate.edu", true),
					new ResultPair("battle.net", true),
					new ResultPair("face.com.book", false),
					new ResultPair("www.wikipedia.org", true),
					new ResultPair("a.b.c", false),
					new ResultPair("adsfqewr", false),
					new ResultPair("asdf.123", false)
					new ResultPair("go.a", false),
                                	new ResultPair("go.a1a", false),
                               	 	new ResultPair("go.cc", true),
                                  	new ResultPair("go.1aa", false),
                                  	new ResultPair("aaa.", false),
                                  	new ResultPair(".aaa", false),
                                  	new ResultPair("aaa", false),
                                  	new ResultPair("", false)};	


	//test port
	ResultPair[] testUrlPort = 	{new ResultPair(":80", true),
                             		new ResultPair(":65535", true), // max possible
                             		new ResultPair(":65536", false), // max possible +1
                             		new ResultPair(":0", true),
                             		new ResultPair("", true),
                             		new ResultPair(":-1", false),
                             		new ResultPair(":65636", false),
                             		new ResultPair(":999999999999999999", false),
                             		new ResultPair(":65a", false)};	



	//test path
	ResultPair[] testPath = 	{new ResultPair("/test1", true),
                          		new ResultPair("/t123", true),
                          		new ResultPair("/$23", true),
                          		new ResultPair("/..", false),
                          		new ResultPair("/../", false),
                          		new ResultPair("/test1/", true),
                          		new ResultPair("", true),
                          		new ResultPair("/test1/file", true),
                          		new ResultPair("/..//file", false),
                          		new ResultPair("/test1//file", false)};


	
	//test query
	ResultPair[] testUrlQuery = 	{new ResultPair("?action=view", true),
                              		new ResultPair("?action=edit&mode=up", true),
                              		new ResultPair("", true)};


	
	Object[] testUrlParts = {schemeTest, authorityTest, portTest, pathTest, queryTest};
	Object[] testUrlPartsOptions = {schemeTest, authorityTest, portTest, pathTest, queryTest};
	int[] testPartsIndex = {0, 0, 0, 0, 0};



