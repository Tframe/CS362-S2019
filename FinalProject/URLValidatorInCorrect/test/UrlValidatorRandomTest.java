import org.junit.Test;
import java.util.Random;

public class UrlValidatorRandomTest {
    @Test
    public void testIsValid() {
        long options =
                UrlValidator.ALLOW_2_SLASHES
                        + UrlValidator.ALLOW_ALL_SCHEMES
                        + UrlValidator.NO_FRAGMENTS;

        ResultPair urlTestCase = buildTestURL();
        System.out.println(urlTestCase.item);
        System.out.println(urlTestCase.valid);
    }

    private ResultPair buildTestURL() {
        int randIdx;
        boolean expected;
        Random randomGen = new Random();
        StringBuilder urlBuilder = new StringBuilder();


        // Build Scheme
        randIdx = randomGen.nextInt(testUrlScheme.length);
        urlBuilder.append(testUrlScheme[randIdx].item);
        expected = testUrlScheme[randIdx].valid;

        // Build Authority
        randIdx = randomGen.nextInt(testUrlAuthority.length);
        urlBuilder.append(testUrlAuthority[randIdx].item);
        expected = testUrlAuthority[randIdx].valid && expected;

        // Build Port
        randIdx = randomGen.nextInt(testUrlPort.length);
        urlBuilder.append(testUrlPort[randIdx].item);
        expected = testUrlPort[randIdx].valid && expected;

        // Build Path
        randIdx = randomGen.nextInt(testPath.length);
        urlBuilder.append(testPath[randIdx].item);
        expected = testPath[randIdx].valid && expected;

//        // Build Fragment
//        randIdx = randomGen.nextInt(test.length);
//        urlBuilder.append(testUrlScheme[randIdx].item);
//        expected = testUrlScheme[randIdx].valid;

        String urlToTest = urlBuilder.toString();

        return new ResultPair(urlToTest, expected);
    }


    /* Pairs taken from URLValidatorCorrect for random testing */
    private ResultPair[] testUrlScheme = {new ResultPair("http://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", true),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("://", false)};

    private ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
            new ResultPair("www.google.com.", true),
            new ResultPair("go.com", true),
            new ResultPair("go.au", true),
            new ResultPair("0.0.0.0", true),
            new ResultPair("255.255.255.255", true),
            new ResultPair("256.256.256.256", false),
            new ResultPair("255.com", true),
            new ResultPair("1.2.3.4.5", false),
            new ResultPair("1.2.3.4.", false),
            new ResultPair("1.2.3", false),
            new ResultPair(".1.2.3.4", false),
            new ResultPair("go.a", false),
            new ResultPair("go.a1a", false),
            new ResultPair("go.cc", true),
            new ResultPair("go.1aa", false),
            new ResultPair("aaa.", false),
            new ResultPair(".aaa", false),
            new ResultPair("aaa", false),
            new ResultPair("", false)
    };
    private ResultPair[] testUrlPort = {new ResultPair(":80", true),
            new ResultPair(":65535", true), // max possible
            new ResultPair(":65536", false), // max possible +1
            new ResultPair(":0", true),
            new ResultPair("", true),
            new ResultPair(":-1", false),
            new ResultPair(":65636", false),
            new ResultPair(":999999999999999999", false),
            new ResultPair(":65a", false)
    };
    private ResultPair[] testPath = {new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", false)
    };
    //Test allow2slash, noFragment
    private ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("/#", false),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/t123/file", true),
            new ResultPair("/$23/file", true),
            new ResultPair("/../file", false),
            new ResultPair("/..//file", false),
            new ResultPair("/test1//file", true),
            new ResultPair("/#/file", false)
    };

    private ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true)
    };
}
