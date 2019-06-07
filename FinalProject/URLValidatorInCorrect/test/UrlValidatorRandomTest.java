import org.junit.Before;
import org.junit.Test;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.MatcherAssert.assertThat;
import java.util.Random;

public class UrlValidatorRandomTest {
    private UrlValidator urlValidator;

    @Before
    public void init() {
        long options = UrlValidator.ALLOW_2_SLASHES
                + UrlValidator.ALLOW_ALL_SCHEMES
                + UrlValidator.NO_FRAGMENTS;
        urlValidator = new UrlValidator(null, null, options);
    }

    @Test
    public void randomTestIsValid() {
        short NUM_TEST_CASES = 500;

        for (int i = 0; i < NUM_TEST_CASES; i++) {
            ResultPair urlTestCase = buildTestURL();
            String urlToTest = urlTestCase.item;
            boolean expected = urlTestCase.valid;

            assertThat(urlToTest, urlValidator.isValid(urlToTest), is(expected));
        }

        System.out.println(String.format("All %d test cases passed.", NUM_TEST_CASES));
    }

    private ResultPair buildTestURL() {
        int randIdx;
        boolean expected = true;
        Random randomGen = new Random();
        StringBuilder urlBuilder = new StringBuilder();

        for (ResultPair[] partition: testPartitions) {
            randIdx = randomGen.nextInt(partition.length - 1);
            urlBuilder.append(partition[randIdx].item);
            expected &= partition[randIdx].valid;
        }

        String urlToTest = urlBuilder.toString();

        return new ResultPair(urlToTest, expected);
    }


    /* Pairs taken from URLValidatorCorrect for random testing */
    private ResultPair[] testUrlScheme = {
            new ResultPair("http://", true),
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
            new ResultPair("/test3//file", true)
    };

    private ResultPair[] testUrlQuery = {
            new ResultPair("?action=view", true),
            new ResultPair("?action=edit&mode=up", true),
            new ResultPair("", true),
            new ResultPair("?hi=test", true),
    };

    private ResultPair[][] testPartitions = { testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery };
}
