fill out a config file located in the same directory as the test.exe executable
Example
```xml
<cfg>
    <cam>
        <cameraId>0</cameraId>
        <cameraName>Main Camera</cameraName>
        <rtspUrl></rtspUrl> <!-- Real time streaming protocol URL -->
        <valid>1</valid> <!-- 0 false, 1 true-->
        <imgW>960</imgW> <!-- Image Width -->
        <imgH>630</imgH> <!-- Image Height -->
        <fpsNum>30</fpsNum> <!-- frames per second numerator -->
        <fpsDen>1</fpsDen> <!-- frames per second denominator -->
        <frmQueSz>10</frmQueSz>
        <detPyrLev>1</detPyrLev>
        <detMethodId>0</detMethodId>
        <detNetworkId>0</detNetworkId>
        <detFrmsToSkip>2</detFrmsToSkip>
        <mp4LocationAndPrefix>record</mp4LocationAndPrefix>
    </cam>
    <hygrometer>
        <hygrometerId>0</hygrometerId>
        <hygrometerName>Main Hygrometer</hygrometerName>
    </hygrometer>
    <thermometer>
        <thermometerId>0</thermometerId>
        <thermometerName>Main Hygrometer</thermometerName>
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