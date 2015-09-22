bq query --allow_large_results --destination_table AMS.timeInSecInData 'SELECT INTEGER(JMDCTime) AS JMDCTimeInSec FROM AMS.Data GROUP BY JMDCTimeInSec ORDER BY JMDCTimeInSec'

