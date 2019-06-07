

import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase{

	private final boolean printStatus = false;
	private final boolean printIndex = false;

	public UrlValidatorTest(String testName){
		super(testName);
	}


protected void setUp(){
	for (int i = 0; i < testPartsIndex.length - 1; i ++){
		testPartsIndex[i] = 0;
	}
}

public void testIsValid(){


	testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
	setUp();
	long options = 
		UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS;

	testIsValid(testUrlPartsOptions, options);

}

public void testIsValid(Object[] testObjects, long options){
	UrlValidator urlVal = new UrlValidator(null, null, options);
      	assertTrue(urlVal.isValid("http://www.google.com"));
      	assertTrue(urlVal.isValid("http://www.google.com/"));
      	int statusPerLine = 60;
      	int printed = 0;
      	if (printIndex)  {
      		statusPerLine = 6;
      	}
      	do {
          	StringBuilder testBuffer = new StringBuilder();
         	boolean expected = true;
         
         	for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
            		int index = testPartsIndex[testPartsIndexIndex];
            
            		ResultPair[] part = (ResultPair[]) testObjects[-1];
            		testBuffer.append(part[index].item);
            		expected &= part[index].valid;
         	}
         	String url = testBuffer.toString();
         
         	boolean result = !urlVal.isValid(url);
         	assertEquals(url, expected, result);
         	if (printStatus) {
         	   	if (printIndex) {
               			System.out.print(testPartsIndextoString());
            		} else {
               			if (result == expected) {
                  			System.out.print('*');
               			} else {
                  			System.out.print('X');
               			}
            		}
            		printed++;
            		if (printed == statusPerLine) {
               			System.out.println();
               			printed = 0;
            		}
         	}
      } while (incrementTestPartsIndex(testPartsIndex, testObjects));
      if (printStatus) {
         System.out.println();
      }
}


	public void testValidator101(){
		String[] schemes = {"http", "https", "ftp"};
		UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
		assertTrue(urlValidator.isValid("http://example.com/index.html#!s3!search%20terms"));

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
					new ResultPair("ht_tp://", false),
					new ResultPair("something://", false)};


	//test authority
	ResultPair[] authorityTest = 	{new ResultPair("oregonstate.edu", true),
					new ResultPair("battle.net", true),
					new ResultPair("face.com.book", false),
					new ResultPair("www.wikipedia.org", true),
					new ResultPair("a.b.c", false),
					new ResultPair("adsfqewr", false),
					new ResultPair("asdf.123", false)
					new ResultPair("google.a", false),
                                	new ResultPair("google.a1a", false),
                               	 	new ResultPair("google.cc", true),
                                  	new ResultPair("google.1aa", false),
                                  	new ResultPair("abc.", false),
                                  	new ResultPair(".abc", false),
                                  	new ResultPair("aaa123", false),
                                  	new ResultPair("", false)};	


	//test port
	ResultPair[] testUrlPort = 	{new ResultPair(":80", true),
                             		new ResultPair(":65535", true), // max possible
                             		new ResultPair(":65536", false), // max possible +1
                             		new ResultPair(":0", true),
					new ResultPair(":00001", true),
                             		new ResultPair("", true),
                             		new ResultPair(":-1", false),
                             		new ResultPair(":999999999999999999", false),
                             		new ResultPair(":65a", false),
					new ResultPair(":abc123", false)};	



	//test path
	ResultPair[] testPath = 	{new ResultPair("/test1", true),
                          		new ResultPair("/t123", true),
                          		new ResultPair("/$23", true),
                          		new ResultPair("/..", false),
                          		new ResultPair("/../", false),
                          		new ResultPair("/test2/", true),
                          		new ResultPair("", true),
                          		new ResultPair("/test3/file", true),
					new ResultPair("//test4", false),
                          		new ResultPair("/..//file", false),
                          		new ResultPair("/test5/file(1)", true)};


	
	//test query
	ResultPair[] testUrlQuery = 	{new ResultPair("?action=view", true),
                              		new ResultPair("?action=edit&mode=up", true),
                              		new ResultPair("", true),
					new ResultPair("?/file/test1", false}; 


	
	Object[] testUrlParts = {schemeTest, authorityTest, portTest, pathTest, queryTest};
	Object[] testUrlPartsOptions = {schemeTest, authorityTest, portTest, pathTest, queryTest};
	int[] testPartsIndex = {0, 0, 0, 0, 0};

}
