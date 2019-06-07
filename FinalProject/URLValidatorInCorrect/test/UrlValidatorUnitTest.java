import org.junit.Before;
import org.junit.Test;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;

public class UrlValidatorUnitTest {
    private UrlValidator urlValidator;

    @Before
    public void init() {
        long options = UrlValidator.ALLOW_2_SLASHES
                + UrlValidator.ALLOW_ALL_SCHEMES
                + UrlValidator.NO_FRAGMENTS;
        urlValidator = new UrlValidator(null, null, options);
    }

    @Test
    public void testScheme() {
        String validUrlWithoutScheme = "oregonstate.instructure.com/";

        for (ResultPair scheme : testUrlScheme) {
            boolean expected = scheme.valid;

            String testUrl = scheme.item + validUrlWithoutScheme;
            assertThat(testUrl, urlValidator.isValid(testUrl), is(expected));
        }
    }

    @Test
    public void testAuthority() {
        String validScheme = "http://";

        for (ResultPair authority : testUrlAuthority) {
            boolean expected = authority.valid;

            String testUrl = validScheme + authority.item;
            assertThat(testUrl, urlValidator.isValid(testUrl), is(expected));
        }
    }

    @Test
    public void testPorts() {
        String validUrlWithoutPort = "https://www.facebook.com";

        for (ResultPair port : testUrlPort) {
            boolean expected = port.valid;

            String testUrl = validUrlWithoutPort + port.item;
            assertThat(testUrl, urlValidator.isValid(testUrl), is(expected));
        }
    }

    @Test
    public void testPaths() {
        String validUrlWithoutPath = "https://www.youtube.com";

        for (ResultPair path : testPath) {
            boolean expected = path.valid;

            String testUrl = validUrlWithoutPath + path.item;
            assertThat(testUrl, urlValidator.isValid(testUrl), is(expected));
        }
    }

    @Test
    public void testQueries() {
        String validUrlWithoutQuery = "https://stackoverflow.com/question";

        for (ResultPair query : testUrlQuery) {
            boolean expected = query.valid;

            String testUrl = validUrlWithoutQuery + query.item;
            assertThat(testUrl, urlValidator.isValid(testUrl), is(expected));
        }
    }

    @Test
    public void testUrls() {
        for (ResultPair url : testUrls) {
            boolean expected = url.valid;

            assertThat(url.item, urlValidator.isValid(url.item), is(expected));
        }
    }

    @Test
    public void testFileValidator() {
        String validFile = "file://Documents/Newsletters/Summer2019.pdf";
        assertThat(validFile, urlValidator.isValid(validFile), is(true));

        String invalidFile = "file:://sampledoc.doc";
        assertThat(invalidFile, urlValidator.isValid(invalidFile), is(false));
    }


    /* Pairs taken from URLValidatorCorrect for building unit tests */
    private ResultPair[] testUrlScheme = {
            new ResultPair("http://", true),
            new ResultPair("https://", true),
            new ResultPair("ftp://", true),
            new ResultPair("h3t://", true),
            new ResultPair("3ht://", false),
            new ResultPair("http:/", false),
            new ResultPair("http:", false),
            new ResultPair("http/", false),
            new ResultPair("://", false)
    };

    private ResultPair[] testUrlAuthority = {
            new ResultPair("www.google.com", true),
            new ResultPair("google.com", true),
            new ResultPair("bit.ly", true),
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

    private ResultPair[] testUrlPort = {
            new ResultPair(":80", true),
            new ResultPair(":65535", true), // max possible
            new ResultPair(":65536", false), // max possible +1
            new ResultPair(":0", true),
            new ResultPair("", true),
            new ResultPair(":-1", false),
            new ResultPair(":65636", false),
            new ResultPair(":999999999999999999", false),
            new ResultPair(":65a", false)
    };

    private ResultPair[] testPath = {
            new ResultPair("/test1", true),
            new ResultPair("/t123", true),
            new ResultPair("/$23", true),
            new ResultPair("/..", false),
            new ResultPair("/../", false),
            new ResultPair("/test1/", true),
            new ResultPair("", true),
            new ResultPair("/test1/file", true),
            new ResultPair("/..//file", false),
            new ResultPair("/test3//file", true) // ALLOW_2_SLASHES
    };

    private ResultPair[] testUrlQuery = {
            new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true),
            new ResultPair("?hi=test", true),
    };

    private ResultPair[] testUrls = {
            new ResultPair("https://oregonstate.instructure.com/courses/1719573/assignments/7515087", true),
            new ResultPair("https://github.com/Tframe/CS362-S2019/tree/ProjectPartB-UnitTests/FinalProject/URLValidatorCorrect/test", true),
            new ResultPair("https://www.google.com/search?source=hp&ei=ZvP5XJmMLpK9-gTKs4SgDQ&q=java&oq=java", true),
            new ResultPair("https://www.java.com/en/", true),
            new ResultPair("htp://dksakdas.fakewebsite", false),
            new ResultPair("https://oregonstate.instructure.com:421442/", false),
    };

    private ResultPair[][] testPartitions = { testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery };
}
