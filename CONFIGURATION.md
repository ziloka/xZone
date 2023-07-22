fill out a config file located in the same directory as the test.exe executable
Example
```xml
<cfg>
    <cam>
        <id>0</id>
        <name>Main Camera</name>
        <rtspUrl></rtspUrl> <!-- Real time streaming protocol URL -->
        <valid>1</valid> <!-- 0 false, 1 true-->
        <imgW>960</imgW> <!-- Image Width -->
        <imgH>630</imgH> <!-- Image Height -->
        <fpsNum>30</fpsNum> <!-- frames per second numerator -->
        <fpsDen>1</fpsDen> <!-- frames per second denominator -->

        <!-- a single hertz is one event per second-->
        <frequencyStart>10</frequencyStart> <!-- minimum hertz -->
        <frequencyStep>5</frequencyStep> <!-- interval to step by -->
        <frequencyEnd>100</frequencyEnd> <!-- maximum hertz-->

        <frmQueSz>10</frmQueSz>
        <!-- currently not used configurations -->
        <detPyrLev>1</detPyrLev>
        <detMethodId>0</detMethodId>
        <detNetworkId>0</detNetworkId>
        <detFrmsToSkip>2</detFrmsToSkip>
        <mp4LocationAndPrefix>record</mp4LocationAndPrefix>
    </cam>
    <hygrometer>
        <id>0</id>
        <name>Main Hygrometer</name>
        <mps></mps> <!-- messages per second -->
    </hygrometer>
    <thermometer>
        <id>0</id>
        <name>Main Hygrometer</name>
        <mps></mps> <!-- messages per second -->
    </thermometer>
    <log>
        <appRootFolder>xZone</appRootFolder>
        <logFolder>logs</logFolder>
        <isDumpLog>0</isDumpLog> <!-- 0 false, 1 true-->
        <isShowLogInConsole>1</isShowLogInConsole> <!-- 0 false, 1 true-->
        <frameFreqsToLog>0</frameFreqsToLog>
    </log>
</cfg>
```

Then run test.exe [path to config file]