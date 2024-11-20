/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
$(document).ready(function() {

    $(".click-title").mouseenter( function(    e){
        e.preventDefault();
        this.style.cursor="pointer";
    });
    $(".click-title").mousedown( function(event){
        event.preventDefault();
    });

    // Ugly code while this script is shared among several pages
    try{
        refreshHitsPerSecond(true);
    } catch(e){}
    try{
        refreshResponseTimeOverTime(true);
    } catch(e){}
    try{
        refreshResponseTimePercentiles();
    } catch(e){}
});


var responseTimePercentilesInfos = {
        data: {"result": {"minY": 7.0, "minX": 0.0, "maxY": 72.0, "series": [{"data": [[0.0, 7.0], [0.1, 7.0], [0.2, 7.0], [0.3, 7.0], [0.4, 7.0], [0.5, 7.0], [0.6, 7.0], [0.7, 7.0], [0.8, 7.0], [0.9, 7.0], [1.0, 7.0], [1.1, 7.0], [1.2, 7.0], [1.3, 7.0], [1.4, 7.0], [1.5, 7.0], [1.6, 7.0], [1.7, 7.0], [1.8, 7.0], [1.9, 7.0], [2.0, 7.0], [2.1, 8.0], [2.2, 8.0], [2.3, 8.0], [2.4, 8.0], [2.5, 8.0], [2.6, 8.0], [2.7, 8.0], [2.8, 8.0], [2.9, 8.0], [3.0, 8.0], [3.1, 8.0], [3.2, 8.0], [3.3, 8.0], [3.4, 8.0], [3.5, 8.0], [3.6, 8.0], [3.7, 8.0], [3.8, 8.0], [3.9, 8.0], [4.0, 8.0], [4.1, 8.0], [4.2, 8.0], [4.3, 8.0], [4.4, 8.0], [4.5, 8.0], [4.6, 8.0], [4.7, 8.0], [4.8, 8.0], [4.9, 8.0], [5.0, 8.0], [5.1, 8.0], [5.2, 8.0], [5.3, 8.0], [5.4, 8.0], [5.5, 8.0], [5.6, 8.0], [5.7, 8.0], [5.8, 8.0], [5.9, 8.0], [6.0, 8.0], [6.1, 8.0], [6.2, 8.0], [6.3, 8.0], [6.4, 8.0], [6.5, 8.0], [6.6, 8.0], [6.7, 8.0], [6.8, 8.0], [6.9, 8.0], [7.0, 8.0], [7.1, 8.0], [7.2, 8.0], [7.3, 8.0], [7.4, 8.0], [7.5, 8.0], [7.6, 8.0], [7.7, 9.0], [7.8, 9.0], [7.9, 9.0], [8.0, 9.0], [8.1, 9.0], [8.2, 9.0], [8.3, 9.0], [8.4, 9.0], [8.5, 9.0], [8.6, 9.0], [8.7, 9.0], [8.8, 9.0], [8.9, 9.0], [9.0, 9.0], [9.1, 9.0], [9.2, 9.0], [9.3, 9.0], [9.4, 9.0], [9.5, 9.0], [9.6, 9.0], [9.7, 9.0], [9.8, 10.0], [9.9, 10.0], [10.0, 10.0], [10.1, 10.0], [10.2, 10.0], [10.3, 10.0], [10.4, 10.0], [10.5, 10.0], [10.6, 11.0], [10.7, 11.0], [10.8, 12.0], [10.9, 12.0], [11.0, 12.0], [11.1, 12.0], [11.2, 12.0], [11.3, 12.0], [11.4, 13.0], [11.5, 13.0], [11.6, 13.0], [11.7, 13.0], [11.8, 13.0], [11.9, 13.0], [12.0, 13.0], [12.1, 13.0], [12.2, 13.0], [12.3, 13.0], [12.4, 13.0], [12.5, 13.0], [12.6, 13.0], [12.7, 13.0], [12.8, 13.0], [12.9, 13.0], [13.0, 13.0], [13.1, 13.0], [13.2, 13.0], [13.3, 13.0], [13.4, 13.0], [13.5, 13.0], [13.6, 13.0], [13.7, 13.0], [13.8, 13.0], [13.9, 13.0], [14.0, 13.0], [14.1, 13.0], [14.2, 13.0], [14.3, 13.0], [14.4, 13.0], [14.5, 13.0], [14.6, 13.0], [14.7, 13.0], [14.8, 13.0], [14.9, 13.0], [15.0, 13.0], [15.1, 13.0], [15.2, 13.0], [15.3, 13.0], [15.4, 13.0], [15.5, 13.0], [15.6, 13.0], [15.7, 13.0], [15.8, 13.0], [15.9, 13.0], [16.0, 13.0], [16.1, 13.0], [16.2, 13.0], [16.3, 13.0], [16.4, 13.0], [16.5, 13.0], [16.6, 13.0], [16.7, 13.0], [16.8, 13.0], [16.9, 13.0], [17.0, 13.0], [17.1, 13.0], [17.2, 13.0], [17.3, 13.0], [17.4, 13.0], [17.5, 13.0], [17.6, 13.0], [17.7, 13.0], [17.8, 13.0], [17.9, 13.0], [18.0, 13.0], [18.1, 13.0], [18.2, 13.0], [18.3, 13.0], [18.4, 13.0], [18.5, 13.0], [18.6, 13.0], [18.7, 13.0], [18.8, 13.0], [18.9, 13.0], [19.0, 13.0], [19.1, 13.0], [19.2, 13.0], [19.3, 13.0], [19.4, 13.0], [19.5, 13.0], [19.6, 13.0], [19.7, 13.0], [19.8, 13.0], [19.9, 13.0], [20.0, 13.0], [20.1, 13.0], [20.2, 13.0], [20.3, 13.0], [20.4, 13.0], [20.5, 13.0], [20.6, 13.0], [20.7, 13.0], [20.8, 13.0], [20.9, 13.0], [21.0, 13.0], [21.1, 13.0], [21.2, 13.0], [21.3, 13.0], [21.4, 13.0], [21.5, 13.0], [21.6, 13.0], [21.7, 13.0], [21.8, 13.0], [21.9, 13.0], [22.0, 13.0], [22.1, 13.0], [22.2, 13.0], [22.3, 13.0], [22.4, 13.0], [22.5, 13.0], [22.6, 13.0], [22.7, 13.0], [22.8, 13.0], [22.9, 13.0], [23.0, 13.0], [23.1, 13.0], [23.2, 13.0], [23.3, 13.0], [23.4, 13.0], [23.5, 13.0], [23.6, 13.0], [23.7, 13.0], [23.8, 13.0], [23.9, 13.0], [24.0, 13.0], [24.1, 13.0], [24.2, 13.0], [24.3, 13.0], [24.4, 13.0], [24.5, 13.0], [24.6, 13.0], [24.7, 13.0], [24.8, 13.0], [24.9, 13.0], [25.0, 13.0], [25.1, 13.0], [25.2, 13.0], [25.3, 13.0], [25.4, 13.0], [25.5, 13.0], [25.6, 13.0], [25.7, 13.0], [25.8, 13.0], [25.9, 13.0], [26.0, 13.0], [26.1, 13.0], [26.2, 13.0], [26.3, 13.0], [26.4, 13.0], [26.5, 13.0], [26.6, 13.0], [26.7, 13.0], [26.8, 13.0], [26.9, 13.0], [27.0, 13.0], [27.1, 13.0], [27.2, 13.0], [27.3, 13.0], [27.4, 13.0], [27.5, 13.0], [27.6, 13.0], [27.7, 13.0], [27.8, 13.0], [27.9, 13.0], [28.0, 13.0], [28.1, 13.0], [28.2, 13.0], [28.3, 13.0], [28.4, 13.0], [28.5, 13.0], [28.6, 13.0], [28.7, 13.0], [28.8, 13.0], [28.9, 13.0], [29.0, 13.0], [29.1, 13.0], [29.2, 13.0], [29.3, 13.0], [29.4, 13.0], [29.5, 13.0], [29.6, 13.0], [29.7, 13.0], [29.8, 13.0], [29.9, 13.0], [30.0, 13.0], [30.1, 13.0], [30.2, 13.0], [30.3, 13.0], [30.4, 13.0], [30.5, 13.0], [30.6, 13.0], [30.7, 13.0], [30.8, 13.0], [30.9, 13.0], [31.0, 13.0], [31.1, 13.0], [31.2, 13.0], [31.3, 13.0], [31.4, 13.0], [31.5, 13.0], [31.6, 13.0], [31.7, 13.0], [31.8, 13.0], [31.9, 13.0], [32.0, 13.0], [32.1, 13.0], [32.2, 13.0], [32.3, 13.0], [32.4, 13.0], [32.5, 13.0], [32.6, 13.0], [32.7, 13.0], [32.8, 13.0], [32.9, 13.0], [33.0, 13.0], [33.1, 13.0], [33.2, 13.0], [33.3, 13.0], [33.4, 13.0], [33.5, 13.0], [33.6, 13.0], [33.7, 13.0], [33.8, 13.0], [33.9, 13.0], [34.0, 13.0], [34.1, 13.0], [34.2, 13.0], [34.3, 13.0], [34.4, 13.0], [34.5, 13.0], [34.6, 13.0], [34.7, 13.0], [34.8, 13.0], [34.9, 13.0], [35.0, 13.0], [35.1, 13.0], [35.2, 13.0], [35.3, 13.0], [35.4, 13.0], [35.5, 13.0], [35.6, 13.0], [35.7, 13.0], [35.8, 13.0], [35.9, 13.0], [36.0, 13.0], [36.1, 13.0], [36.2, 13.0], [36.3, 13.0], [36.4, 13.0], [36.5, 13.0], [36.6, 13.0], [36.7, 13.0], [36.8, 13.0], [36.9, 13.0], [37.0, 13.0], [37.1, 13.0], [37.2, 13.0], [37.3, 13.0], [37.4, 13.0], [37.5, 13.0], [37.6, 13.0], [37.7, 13.0], [37.8, 13.0], [37.9, 13.0], [38.0, 13.0], [38.1, 13.0], [38.2, 13.0], [38.3, 13.0], [38.4, 13.0], [38.5, 13.0], [38.6, 13.0], [38.7, 13.0], [38.8, 13.0], [38.9, 13.0], [39.0, 13.0], [39.1, 13.0], [39.2, 13.0], [39.3, 13.0], [39.4, 13.0], [39.5, 13.0], [39.6, 13.0], [39.7, 13.0], [39.8, 13.0], [39.9, 13.0], [40.0, 13.0], [40.1, 13.0], [40.2, 13.0], [40.3, 13.0], [40.4, 13.0], [40.5, 13.0], [40.6, 13.0], [40.7, 13.0], [40.8, 13.0], [40.9, 13.0], [41.0, 13.0], [41.1, 13.0], [41.2, 13.0], [41.3, 13.0], [41.4, 13.0], [41.5, 13.0], [41.6, 13.0], [41.7, 13.0], [41.8, 13.0], [41.9, 13.0], [42.0, 13.0], [42.1, 13.0], [42.2, 13.0], [42.3, 13.0], [42.4, 13.0], [42.5, 13.0], [42.6, 13.0], [42.7, 13.0], [42.8, 13.0], [42.9, 13.0], [43.0, 13.0], [43.1, 13.0], [43.2, 13.0], [43.3, 13.0], [43.4, 13.0], [43.5, 13.0], [43.6, 13.0], [43.7, 13.0], [43.8, 13.0], [43.9, 13.0], [44.0, 13.0], [44.1, 13.0], [44.2, 13.0], [44.3, 13.0], [44.4, 13.0], [44.5, 13.0], [44.6, 13.0], [44.7, 13.0], [44.8, 13.0], [44.9, 13.0], [45.0, 13.0], [45.1, 13.0], [45.2, 13.0], [45.3, 13.0], [45.4, 13.0], [45.5, 13.0], [45.6, 13.0], [45.7, 13.0], [45.8, 13.0], [45.9, 13.0], [46.0, 13.0], [46.1, 13.0], [46.2, 13.0], [46.3, 13.0], [46.4, 13.0], [46.5, 13.0], [46.6, 13.0], [46.7, 13.0], [46.8, 13.0], [46.9, 13.0], [47.0, 13.0], [47.1, 13.0], [47.2, 13.0], [47.3, 13.0], [47.4, 13.0], [47.5, 13.0], [47.6, 13.0], [47.7, 13.0], [47.8, 13.0], [47.9, 13.0], [48.0, 13.0], [48.1, 13.0], [48.2, 13.0], [48.3, 13.0], [48.4, 13.0], [48.5, 13.0], [48.6, 13.0], [48.7, 13.0], [48.8, 13.0], [48.9, 13.0], [49.0, 13.0], [49.1, 13.0], [49.2, 13.0], [49.3, 13.0], [49.4, 13.0], [49.5, 13.0], [49.6, 13.0], [49.7, 13.0], [49.8, 13.0], [49.9, 13.0], [50.0, 13.0], [50.1, 13.0], [50.2, 13.0], [50.3, 13.0], [50.4, 13.0], [50.5, 13.0], [50.6, 13.0], [50.7, 13.0], [50.8, 13.0], [50.9, 13.0], [51.0, 13.0], [51.1, 13.0], [51.2, 13.0], [51.3, 13.0], [51.4, 13.0], [51.5, 13.0], [51.6, 13.0], [51.7, 13.0], [51.8, 14.0], [51.9, 14.0], [52.0, 14.0], [52.1, 14.0], [52.2, 14.0], [52.3, 14.0], [52.4, 14.0], [52.5, 14.0], [52.6, 14.0], [52.7, 14.0], [52.8, 14.0], [52.9, 14.0], [53.0, 14.0], [53.1, 14.0], [53.2, 14.0], [53.3, 14.0], [53.4, 14.0], [53.5, 14.0], [53.6, 14.0], [53.7, 14.0], [53.8, 14.0], [53.9, 14.0], [54.0, 14.0], [54.1, 14.0], [54.2, 14.0], [54.3, 14.0], [54.4, 14.0], [54.5, 14.0], [54.6, 14.0], [54.7, 14.0], [54.8, 14.0], [54.9, 14.0], [55.0, 14.0], [55.1, 14.0], [55.2, 14.0], [55.3, 14.0], [55.4, 14.0], [55.5, 14.0], [55.6, 14.0], [55.7, 14.0], [55.8, 14.0], [55.9, 14.0], [56.0, 14.0], [56.1, 14.0], [56.2, 14.0], [56.3, 14.0], [56.4, 14.0], [56.5, 14.0], [56.6, 14.0], [56.7, 14.0], [56.8, 14.0], [56.9, 14.0], [57.0, 14.0], [57.1, 14.0], [57.2, 14.0], [57.3, 14.0], [57.4, 14.0], [57.5, 14.0], [57.6, 14.0], [57.7, 14.0], [57.8, 14.0], [57.9, 14.0], [58.0, 14.0], [58.1, 14.0], [58.2, 14.0], [58.3, 14.0], [58.4, 14.0], [58.5, 14.0], [58.6, 14.0], [58.7, 14.0], [58.8, 14.0], [58.9, 14.0], [59.0, 14.0], [59.1, 14.0], [59.2, 14.0], [59.3, 14.0], [59.4, 14.0], [59.5, 14.0], [59.6, 14.0], [59.7, 14.0], [59.8, 14.0], [59.9, 14.0], [60.0, 14.0], [60.1, 14.0], [60.2, 14.0], [60.3, 14.0], [60.4, 14.0], [60.5, 14.0], [60.6, 14.0], [60.7, 14.0], [60.8, 14.0], [60.9, 14.0], [61.0, 14.0], [61.1, 14.0], [61.2, 14.0], [61.3, 14.0], [61.4, 14.0], [61.5, 14.0], [61.6, 14.0], [61.7, 14.0], [61.8, 14.0], [61.9, 14.0], [62.0, 14.0], [62.1, 14.0], [62.2, 14.0], [62.3, 14.0], [62.4, 14.0], [62.5, 14.0], [62.6, 14.0], [62.7, 14.0], [62.8, 14.0], [62.9, 14.0], [63.0, 14.0], [63.1, 14.0], [63.2, 14.0], [63.3, 14.0], [63.4, 14.0], [63.5, 14.0], [63.6, 14.0], [63.7, 14.0], [63.8, 14.0], [63.9, 14.0], [64.0, 14.0], [64.1, 14.0], [64.2, 14.0], [64.3, 14.0], [64.4, 14.0], [64.5, 14.0], [64.6, 14.0], [64.7, 14.0], [64.8, 14.0], [64.9, 14.0], [65.0, 14.0], [65.1, 14.0], [65.2, 14.0], [65.3, 14.0], [65.4, 14.0], [65.5, 14.0], [65.6, 14.0], [65.7, 14.0], [65.8, 14.0], [65.9, 14.0], [66.0, 14.0], [66.1, 14.0], [66.2, 14.0], [66.3, 14.0], [66.4, 14.0], [66.5, 14.0], [66.6, 14.0], [66.7, 14.0], [66.8, 14.0], [66.9, 14.0], [67.0, 14.0], [67.1, 14.0], [67.2, 14.0], [67.3, 14.0], [67.4, 14.0], [67.5, 14.0], [67.6, 14.0], [67.7, 14.0], [67.8, 14.0], [67.9, 14.0], [68.0, 14.0], [68.1, 14.0], [68.2, 14.0], [68.3, 14.0], [68.4, 14.0], [68.5, 14.0], [68.6, 14.0], [68.7, 14.0], [68.8, 14.0], [68.9, 14.0], [69.0, 14.0], [69.1, 14.0], [69.2, 14.0], [69.3, 14.0], [69.4, 14.0], [69.5, 14.0], [69.6, 14.0], [69.7, 14.0], [69.8, 14.0], [69.9, 14.0], [70.0, 14.0], [70.1, 14.0], [70.2, 14.0], [70.3, 14.0], [70.4, 14.0], [70.5, 14.0], [70.6, 14.0], [70.7, 14.0], [70.8, 14.0], [70.9, 14.0], [71.0, 14.0], [71.1, 14.0], [71.2, 14.0], [71.3, 14.0], [71.4, 14.0], [71.5, 14.0], [71.6, 14.0], [71.7, 14.0], [71.8, 14.0], [71.9, 14.0], [72.0, 14.0], [72.1, 14.0], [72.2, 14.0], [72.3, 14.0], [72.4, 14.0], [72.5, 14.0], [72.6, 14.0], [72.7, 14.0], [72.8, 14.0], [72.9, 14.0], [73.0, 14.0], [73.1, 14.0], [73.2, 14.0], [73.3, 14.0], [73.4, 14.0], [73.5, 14.0], [73.6, 14.0], [73.7, 14.0], [73.8, 14.0], [73.9, 14.0], [74.0, 14.0], [74.1, 14.0], [74.2, 14.0], [74.3, 14.0], [74.4, 14.0], [74.5, 14.0], [74.6, 14.0], [74.7, 14.0], [74.8, 14.0], [74.9, 14.0], [75.0, 14.0], [75.1, 14.0], [75.2, 14.0], [75.3, 14.0], [75.4, 14.0], [75.5, 14.0], [75.6, 14.0], [75.7, 14.0], [75.8, 14.0], [75.9, 14.0], [76.0, 14.0], [76.1, 14.0], [76.2, 14.0], [76.3, 14.0], [76.4, 14.0], [76.5, 14.0], [76.6, 14.0], [76.7, 14.0], [76.8, 14.0], [76.9, 14.0], [77.0, 14.0], [77.1, 14.0], [77.2, 14.0], [77.3, 14.0], [77.4, 14.0], [77.5, 14.0], [77.6, 14.0], [77.7, 14.0], [77.8, 14.0], [77.9, 14.0], [78.0, 14.0], [78.1, 14.0], [78.2, 14.0], [78.3, 14.0], [78.4, 14.0], [78.5, 14.0], [78.6, 14.0], [78.7, 14.0], [78.8, 14.0], [78.9, 14.0], [79.0, 14.0], [79.1, 14.0], [79.2, 14.0], [79.3, 14.0], [79.4, 14.0], [79.5, 14.0], [79.6, 14.0], [79.7, 14.0], [79.8, 14.0], [79.9, 14.0], [80.0, 14.0], [80.1, 14.0], [80.2, 14.0], [80.3, 14.0], [80.4, 14.0], [80.5, 14.0], [80.6, 14.0], [80.7, 14.0], [80.8, 14.0], [80.9, 14.0], [81.0, 14.0], [81.1, 14.0], [81.2, 14.0], [81.3, 14.0], [81.4, 14.0], [81.5, 14.0], [81.6, 14.0], [81.7, 14.0], [81.8, 14.0], [81.9, 14.0], [82.0, 14.0], [82.1, 14.0], [82.2, 14.0], [82.3, 14.0], [82.4, 14.0], [82.5, 14.0], [82.6, 14.0], [82.7, 14.0], [82.8, 14.0], [82.9, 14.0], [83.0, 14.0], [83.1, 14.0], [83.2, 14.0], [83.3, 14.0], [83.4, 14.0], [83.5, 14.0], [83.6, 14.0], [83.7, 14.0], [83.8, 14.0], [83.9, 14.0], [84.0, 14.0], [84.1, 14.0], [84.2, 14.0], [84.3, 14.0], [84.4, 14.0], [84.5, 14.0], [84.6, 14.0], [84.7, 15.0], [84.8, 15.0], [84.9, 15.0], [85.0, 15.0], [85.1, 15.0], [85.2, 15.0], [85.3, 15.0], [85.4, 15.0], [85.5, 15.0], [85.6, 15.0], [85.7, 15.0], [85.8, 15.0], [85.9, 15.0], [86.0, 15.0], [86.1, 15.0], [86.2, 15.0], [86.3, 15.0], [86.4, 15.0], [86.5, 15.0], [86.6, 15.0], [86.7, 15.0], [86.8, 15.0], [86.9, 15.0], [87.0, 15.0], [87.1, 15.0], [87.2, 15.0], [87.3, 15.0], [87.4, 15.0], [87.5, 15.0], [87.6, 15.0], [87.7, 15.0], [87.8, 15.0], [87.9, 15.0], [88.0, 15.0], [88.1, 15.0], [88.2, 15.0], [88.3, 15.0], [88.4, 15.0], [88.5, 15.0], [88.6, 15.0], [88.7, 15.0], [88.8, 15.0], [88.9, 15.0], [89.0, 15.0], [89.1, 15.0], [89.2, 15.0], [89.3, 15.0], [89.4, 15.0], [89.5, 15.0], [89.6, 15.0], [89.7, 15.0], [89.8, 15.0], [89.9, 15.0], [90.0, 15.0], [90.1, 15.0], [90.2, 15.0], [90.3, 15.0], [90.4, 15.0], [90.5, 15.0], [90.6, 15.0], [90.7, 15.0], [90.8, 15.0], [90.9, 15.0], [91.0, 15.0], [91.1, 15.0], [91.2, 15.0], [91.3, 15.0], [91.4, 15.0], [91.5, 15.0], [91.6, 15.0], [91.7, 15.0], [91.8, 15.0], [91.9, 15.0], [92.0, 15.0], [92.1, 15.0], [92.2, 15.0], [92.3, 15.0], [92.4, 15.0], [92.5, 15.0], [92.6, 15.0], [92.7, 15.0], [92.8, 15.0], [92.9, 15.0], [93.0, 16.0], [93.1, 16.0], [93.2, 16.0], [93.3, 16.0], [93.4, 16.0], [93.5, 16.0], [93.6, 16.0], [93.7, 16.0], [93.8, 16.0], [93.9, 16.0], [94.0, 16.0], [94.1, 16.0], [94.2, 16.0], [94.3, 16.0], [94.4, 16.0], [94.5, 16.0], [94.6, 16.0], [94.7, 16.0], [94.8, 16.0], [94.9, 16.0], [95.0, 16.0], [95.1, 16.0], [95.2, 16.0], [95.3, 16.0], [95.4, 16.0], [95.5, 16.0], [95.6, 16.0], [95.7, 16.0], [95.8, 16.0], [95.9, 16.0], [96.0, 16.0], [96.1, 16.0], [96.2, 16.0], [96.3, 16.0], [96.4, 16.0], [96.5, 16.0], [96.6, 16.0], [96.7, 16.0], [96.8, 16.0], [96.9, 16.0], [97.0, 16.0], [97.1, 16.0], [97.2, 16.0], [97.3, 16.0], [97.4, 16.0], [97.5, 16.0], [97.6, 16.0], [97.7, 16.0], [97.8, 16.0], [97.9, 17.0], [98.0, 17.0], [98.1, 17.0], [98.2, 17.0], [98.3, 17.0], [98.4, 17.0], [98.5, 18.0], [98.6, 18.0], [98.7, 18.0], [98.8, 18.0], [98.9, 19.0], [99.0, 19.0], [99.1, 19.0], [99.2, 19.0], [99.3, 19.0], [99.4, 19.0], [99.5, 19.0], [99.6, 20.0], [99.7, 20.0], [99.8, 20.0], [99.9, 26.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 100.0, "title": "Response Time Percentiles"}},
        getOptions: function() {
            return {
                series: {
                    points: { show: false }
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimePercentiles'
                },
                xaxis: {
                    tickDecimals: 1,
                    axisLabel: "Percentiles",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Percentile value in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : %x.2 percentile was %y ms"
                },
                selection: { mode: "xy" },
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimePercentiles"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimesPercentiles"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimesPercentiles"), dataset, prepareOverviewOptions(options));
        }
};

/**
 * @param elementId Id of element where we display message
 */
function setEmptyGraph(elementId) {
    $(function() {
        $(elementId).text("No graph series with filter="+seriesFilter);
    });
}

// Response times percentiles
function refreshResponseTimePercentiles() {
    var infos = responseTimePercentilesInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimePercentiles");
        return;
    }
    if (isGraph($("#flotResponseTimesPercentiles"))){
        infos.createGraph();
    } else {
        var choiceContainer = $("#choicesResponseTimePercentiles");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimesPercentiles", "#overviewResponseTimesPercentiles");
        $('#bodyResponseTimePercentiles .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var responseTimeDistributionInfos = {
        data: {"result": {"minY": 2000.0, "minX": 0.0, "maxY": 2000.0, "series": [{"data": [[0.0, 2000.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 100, "maxX": 4.9E-324, "title": "Response Time Distribution"}},
        getOptions: function() {
            var granularity = this.data.result.granularity;
            return {
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimeDistribution'
                },
                xaxis:{
                    axisLabel: "Response times in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of responses",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                bars : {
                    show: true,
                    barWidth: this.data.result.granularity
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: function(label, xval, yval, flotItem){
                        return yval + " responses for " + label + " were between " + xval + " and " + (xval + granularity) + " ms";
                    }
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimeDistribution"), prepareData(data.result.series, $("#choicesResponseTimeDistribution")), options);
        }

};

// Response time distribution
function refreshResponseTimeDistribution() {
    var infos = responseTimeDistributionInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimeDistribution");
        return;
    }
    if (isGraph($("#flotResponseTimeDistribution"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimeDistribution");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        $('#footerResponseTimeDistribution .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var syntheticResponseTimeDistributionInfos = {
        data: {"result": {"minY": 217.0, "minX": 0.0, "ticks": [[0, "Requests having \nresponse time <= 500ms"], [1, "Requests having \nresponse time > 500ms and <= 1,500ms"], [2, "Requests having \nresponse time > 1,500ms"], [3, "Requests in error"]], "maxY": 1783.0, "series": [{"data": [[0.0, 1783.0]], "color": "#9ACD32", "isOverall": false, "label": "Requests having \nresponse time <= 500ms", "isController": false}, {"data": [], "color": "yellow", "isOverall": false, "label": "Requests having \nresponse time > 500ms and <= 1,500ms", "isController": false}, {"data": [], "color": "orange", "isOverall": false, "label": "Requests having \nresponse time > 1,500ms", "isController": false}, {"data": [[3.0, 217.0]], "color": "#FF6347", "isOverall": false, "label": "Requests in error", "isController": false}], "supportsControllersDiscrimination": false, "maxX": 3.0, "title": "Synthetic Response Times Distribution"}},
        getOptions: function() {
            return {
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendSyntheticResponseTimeDistribution'
                },
                xaxis:{
                    axisLabel: "Response times ranges",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                    tickLength:0,
                    min:-0.5,
                    max:3.5
                },
                yaxis: {
                    axisLabel: "Number of responses",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                bars : {
                    show: true,
                    align: "center",
                    barWidth: 0.25,
                    fill:.75
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: function(label, xval, yval, flotItem){
                        return yval + " " + label;
                    }
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var options = this.getOptions();
            prepareOptions(options, data);
            options.xaxis.ticks = data.result.ticks;
            $.plot($("#flotSyntheticResponseTimeDistribution"), prepareData(data.result.series, $("#choicesSyntheticResponseTimeDistribution")), options);
        }

};

// Response time distribution
function refreshSyntheticResponseTimeDistribution() {
    var infos = syntheticResponseTimeDistributionInfos;
    prepareSeries(infos.data, true);
    if (isGraph($("#flotSyntheticResponseTimeDistribution"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesSyntheticResponseTimeDistribution");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        $('#footerSyntheticResponseTimeDistribution .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var activeThreadsOverTimeInfos = {
        data: {"result": {"minY": 1.0, "minX": 1.731747599E12, "maxY": 1.2666666666666666, "series": [{"data": [[1.73174763E12, 1.0], [1.731747632E12, 1.0], [1.731747628E12, 1.0], [1.731747636E12, 1.0], [1.731747634E12, 1.0], [1.731747599E12, 1.2666666666666666], [1.731747642E12, 1.0], [1.731747638E12, 1.0], [1.73174764E12, 1.0], [1.731747603E12, 1.0], [1.731747646E12, 1.0], [1.731747605E12, 1.0], [1.731747648E12, 1.0], [1.731747601E12, 1.0], [1.731747644E12, 1.0], [1.731747609E12, 1.0], [1.731747652E12, 1.0], [1.731747607E12, 1.0], [1.73174765E12, 1.0], [1.731747615E12, 1.0], [1.731747658E12, 1.0], [1.731747611E12, 1.0], [1.731747654E12, 1.0], [1.731747613E12, 1.0], [1.731747656E12, 1.0], [1.731747619E12, 1.0], [1.731747621E12, 1.0], [1.731747617E12, 1.0], [1.731747625E12, 1.0], [1.731747623E12, 1.0], [1.731747631E12, 1.0], [1.731747627E12, 1.0], [1.731747629E12, 1.0], [1.731747635E12, 1.0], [1.731747637E12, 1.0], [1.731747633E12, 1.0], [1.731747641E12, 1.0], [1.7317476E12, 1.0], [1.731747639E12, 1.0], [1.731747604E12, 1.0], [1.731747647E12, 1.0], [1.731747643E12, 1.0], [1.731747645E12, 1.0], [1.731747602E12, 1.0], [1.731747651E12, 1.0], [1.731747653E12, 1.0], [1.73174761E12, 1.0], [1.731747649E12, 1.0], [1.731747606E12, 1.0], [1.731747608E12, 1.0], [1.731747657E12, 1.0], [1.731747614E12, 1.0], [1.731747616E12, 1.0], [1.731747612E12, 1.0], [1.731747655E12, 1.0], [1.73174762E12, 1.0], [1.731747618E12, 1.0], [1.731747626E12, 1.0], [1.731747622E12, 1.0], [1.731747624E12, 1.0]], "isOverall": false, "label": "线程组", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747658E12, "title": "Active Threads Over Time"}},
        getOptions: function() {
            return {
                series: {
                    stack: true,
                    lines: {
                        show: true,
                        fill: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of active threads",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 6,
                    show: true,
                    container: '#legendActiveThreadsOverTime'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                selection: {
                    mode: 'xy'
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : At %x there were %y active threads"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesActiveThreadsOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotActiveThreadsOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewActiveThreadsOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Active Threads Over Time
function refreshActiveThreadsOverTime(fixTimestamps) {
    var infos = activeThreadsOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotActiveThreadsOverTime"))) {
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesActiveThreadsOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotActiveThreadsOverTime", "#overviewActiveThreadsOverTime");
        $('#footerActiveThreadsOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var timeVsThreadsInfos = {
        data: {"result": {"minY": 13.252510040160654, "minX": 1.0, "maxY": 16.375, "series": [{"data": [[1.0, 13.252510040160654], [2.0, 16.375]], "isOverall": false, "label": "Products", "isController": false}, {"data": [[1.003999999999999, 13.264999999999999]], "isOverall": false, "label": "Products-Aggregated", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 2.0, "title": "Time VS Threads"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    axisLabel: "Number of active threads",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response times in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: { noColumns: 2,show: true, container: '#legendTimeVsThreads' },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s: At %x.2 active threads, Average response time was %y.2 ms"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesTimeVsThreads"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotTimesVsThreads"), dataset, options);
            // setup overview
            $.plot($("#overviewTimesVsThreads"), dataset, prepareOverviewOptions(options));
        }
};

// Time vs threads
function refreshTimeVsThreads(){
    var infos = timeVsThreadsInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyTimeVsThreads");
        return;
    }
    if(isGraph($("#flotTimesVsThreads"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTimeVsThreads");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTimesVsThreads", "#overviewTimesVsThreads");
        $('#footerTimeVsThreads .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var bytesThroughputOverTimeInfos = {
        data : {"result": {"minY": 6922.0, "minX": 1.731747599E12, "maxY": 64536.0, "series": [{"data": [[1.73174763E12, 50827.0], [1.731747632E12, 48821.0], [1.731747628E12, 46816.0], [1.731747636E12, 60116.0], [1.731747634E12, 45393.0], [1.731747599E12, 41590.0], [1.731747642E12, 51642.0], [1.731747638E12, 52872.0], [1.73174764E12, 45369.0], [1.731747603E12, 50452.0], [1.731747646E12, 42112.0], [1.731747605E12, 49581.0], [1.731747648E12, 49027.0], [1.731747601E12, 46794.0], [1.731747644E12, 43927.0], [1.731747609E12, 49924.0], [1.731747652E12, 40193.0], [1.731747607E12, 40453.0], [1.73174765E12, 54442.0], [1.731747615E12, 52423.0], [1.731747658E12, 48236.0], [1.731747611E12, 46001.0], [1.731747654E12, 47050.0], [1.731747613E12, 44676.0], [1.731747656E12, 47092.0], [1.731747619E12, 45715.0], [1.731747621E12, 60117.0], [1.731747617E12, 47217.0], [1.731747625E12, 44917.0], [1.731747623E12, 52566.0], [1.731747631E12, 42107.0], [1.731747627E12, 52540.0], [1.731747629E12, 43927.0], [1.731747635E12, 54280.0], [1.731747637E12, 40640.0], [1.731747633E12, 49807.0], [1.731747641E12, 46935.0], [1.7317476E12, 51192.0], [1.731747639E12, 48000.0], [1.731747604E12, 50885.0], [1.731747647E12, 48976.0], [1.731747643E12, 48330.0], [1.731747645E12, 49614.0], [1.731747602E12, 42869.0], [1.731747651E12, 60075.0], [1.731747653E12, 53634.0], [1.73174761E12, 45542.0], [1.731747649E12, 46024.0], [1.731747606E12, 64536.0], [1.731747608E12, 51094.0], [1.731747657E12, 52176.0], [1.731747614E12, 43674.0], [1.731747616E12, 42115.0], [1.731747612E12, 53477.0], [1.731747655E12, 45115.0], [1.73174762E12, 53696.0], [1.731747618E12, 51404.0], [1.731747626E12, 46171.0], [1.731747622E12, 40772.0], [1.731747624E12, 48923.0]], "isOverall": false, "label": "Bytes received per second", "isController": false}, {"data": [[1.73174763E12, 8077.0], [1.731747632E12, 7824.0], [1.731747628E12, 7181.0], [1.731747636E12, 8662.0], [1.731747634E12, 7247.0], [1.731747599E12, 7182.0], [1.731747642E12, 8570.0], [1.731747638E12, 8034.0], [1.73174764E12, 7095.0], [1.731747603E12, 8596.0], [1.731747646E12, 7263.0], [1.731747605E12, 7221.0], [1.731747648E12, 8389.0], [1.731747601E12, 7992.0], [1.731747644E12, 8334.0], [1.731747609E12, 8696.0], [1.731747652E12, 7110.0], [1.731747607E12, 7167.0], [1.73174765E12, 7920.0], [1.731747615E12, 8302.0], [1.731747658E12, 7169.0], [1.731747611E12, 8019.0], [1.731747654E12, 8473.0], [1.731747613E12, 7172.0], [1.731747656E12, 8010.0], [1.731747619E12, 7277.0], [1.731747621E12, 8677.0], [1.731747617E12, 7572.0], [1.731747625E12, 7083.0], [1.731747623E12, 8011.0], [1.731747631E12, 7263.0], [1.731747627E12, 8555.0], [1.731747629E12, 8325.0], [1.731747635E12, 7926.0], [1.731747637E12, 7129.0], [1.731747633E12, 8400.0], [1.731747641E12, 7989.0], [1.7317476E12, 8500.0], [1.731747639E12, 8467.0], [1.731747604E12, 7956.0], [1.731747647E12, 7858.0], [1.731747643E12, 7175.0], [1.731747645E12, 8050.0], [1.731747602E12, 6922.0], [1.731747651E12, 8644.0], [1.731747653E12, 8035.0], [1.73174761E12, 7083.0], [1.731747649E12, 7257.0], [1.731747606E12, 9373.0], [1.731747608E12, 7749.0], [1.731747657E12, 8585.0], [1.731747614E12, 8091.0], [1.731747616E12, 7290.0], [1.731747612E12, 8555.0], [1.731747655E12, 7086.0], [1.73174762E12, 7899.0], [1.731747618E12, 8625.0], [1.731747626E12, 8001.0], [1.731747622E12, 7148.0], [1.731747624E12, 8471.0]], "isOverall": false, "label": "Bytes sent per second", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747658E12, "title": "Bytes Throughput Over Time"}},
        getOptions : function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity) ,
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Bytes / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendBytesThroughputOverTime'
                },
                selection: {
                    mode: "xy"
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y"
                }
            };
        },
        createGraph : function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesBytesThroughputOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotBytesThroughputOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewBytesThroughputOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Bytes throughput Over Time
function refreshBytesThroughputOverTime(fixTimestamps) {
    var infos = bytesThroughputOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotBytesThroughputOverTime"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesBytesThroughputOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotBytesThroughputOverTime", "#overviewBytesThroughputOverTime");
        $('#footerBytesThroughputOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var responseTimesOverTimeInfos = {
        data: {"result": {"minY": 12.200000000000003, "minX": 1.731747599E12, "maxY": 17.700000000000003, "series": [{"data": [[1.73174763E12, 12.62857142857143], [1.731747632E12, 13.294117647058822], [1.731747628E12, 12.9], [1.731747636E12, 13.5], [1.731747634E12, 13.400000000000002], [1.731747599E12, 17.700000000000003], [1.731747642E12, 13.555555555555555], [1.731747638E12, 13.088235294117649], [1.73174764E12, 15.533333333333333], [1.731747603E12, 13.513513513513516], [1.731747646E12, 12.7], [1.731747605E12, 13.612903225806454], [1.731747648E12, 12.52777777777778], [1.731747601E12, 13.909090909090907], [1.731747644E12, 12.200000000000003], [1.731747609E12, 12.270270270270268], [1.731747652E12, 12.266666666666666], [1.731747607E12, 12.900000000000002], [1.73174765E12, 13.029411764705884], [1.731747615E12, 13.833333333333332], [1.731747658E12, 13.033333333333333], [1.731747611E12, 13.147058823529411], [1.731747654E12, 12.444444444444445], [1.731747613E12, 12.733333333333333], [1.731747656E12, 13.11764705882353], [1.731747619E12, 13.766666666666666], [1.731747621E12, 14.055555555555555], [1.731747617E12, 13.454545454545457], [1.731747625E12, 13.23333333333333], [1.731747623E12, 13.5], [1.731747631E12, 12.533333333333331], [1.731747627E12, 13.555555555555555], [1.731747629E12, 12.485714285714286], [1.731747635E12, 13.294117647058824], [1.731747637E12, 12.699999999999998], [1.731747633E12, 12.555555555555555], [1.731747641E12, 13.294117647058824], [1.7317476E12, 13.702702702702702], [1.731747639E12, 13.277777777777775], [1.731747604E12, 13.3030303030303], [1.731747647E12, 13.294117647058824], [1.731747643E12, 12.799999999999997], [1.731747645E12, 12.600000000000001], [1.731747602E12, 14.133333333333333], [1.731747651E12, 13.472222222222221], [1.731747653E12, 13.294117647058824], [1.73174761E12, 12.833333333333332], [1.731747649E12, 13.066666666666666], [1.731747606E12, 13.769230769230766], [1.731747608E12, 13.51515151515152], [1.731747657E12, 13.749999999999996], [1.731747614E12, 13.235294117647058], [1.731747616E12, 13.466666666666665], [1.731747612E12, 13.611111111111109], [1.731747655E12, 13.2], [1.73174762E12, 13.676470588235293], [1.731747618E12, 12.675675675675675], [1.731747626E12, 13.14705882352941], [1.731747622E12, 12.766666666666667], [1.731747624E12, 12.472222222222227]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747658E12, "title": "Response Time Over Time"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average response time was %y ms"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Response Times Over Time
function refreshResponseTimeOverTime(fixTimestamps) {
    var infos = responseTimesOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimeOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotResponseTimesOverTime"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimesOverTime", "#overviewResponseTimesOverTime");
        $('#footerResponseTimesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var latenciesOverTimeInfos = {
        data: {"result": {"minY": 12.142857142857142, "minX": 1.731747599E12, "maxY": 17.56666666666666, "series": [{"data": [[1.73174763E12, 12.62857142857143], [1.731747632E12, 13.235294117647058], [1.731747628E12, 12.833333333333336], [1.731747636E12, 13.5], [1.731747634E12, 13.400000000000002], [1.731747599E12, 17.56666666666666], [1.731747642E12, 13.555555555555555], [1.731747638E12, 13.058823529411764], [1.73174764E12, 15.433333333333334], [1.731747603E12, 13.486486486486486], [1.731747646E12, 12.666666666666666], [1.731747605E12, 13.612903225806454], [1.731747648E12, 12.5], [1.731747601E12, 13.878787878787877], [1.731747644E12, 12.142857142857142], [1.731747609E12, 12.243243243243242], [1.731747652E12, 12.266666666666666], [1.731747607E12, 12.866666666666667], [1.73174765E12, 12.970588235294116], [1.731747615E12, 13.805555555555555], [1.731747658E12, 13.000000000000002], [1.731747611E12, 13.088235294117647], [1.731747654E12, 12.416666666666666], [1.731747613E12, 12.700000000000003], [1.731747656E12, 13.08823529411765], [1.731747619E12, 13.7], [1.731747621E12, 14.027777777777779], [1.731747617E12, 13.454545454545457], [1.731747625E12, 13.199999999999998], [1.731747623E12, 13.470588235294118], [1.731747631E12, 12.533333333333331], [1.731747627E12, 13.527777777777777], [1.731747629E12, 12.457142857142859], [1.731747635E12, 13.294117647058824], [1.731747637E12, 12.666666666666664], [1.731747633E12, 12.527777777777779], [1.731747641E12, 13.264705882352944], [1.7317476E12, 13.675675675675674], [1.731747639E12, 13.22222222222222], [1.731747604E12, 13.272727272727272], [1.731747647E12, 13.294117647058824], [1.731747643E12, 12.766666666666667], [1.731747645E12, 12.600000000000001], [1.731747602E12, 14.099999999999998], [1.731747651E12, 13.444444444444445], [1.731747653E12, 13.235294117647058], [1.73174761E12, 12.833333333333332], [1.731747649E12, 13.066666666666666], [1.731747606E12, 13.769230769230766], [1.731747608E12, 13.424242424242424], [1.731747657E12, 13.694444444444446], [1.731747614E12, 13.235294117647058], [1.731747616E12, 13.43333333333333], [1.731747612E12, 13.58333333333333], [1.731747655E12, 13.166666666666668], [1.73174762E12, 13.676470588235293], [1.731747618E12, 12.594594594594595], [1.731747626E12, 13.117647058823529], [1.731747622E12, 12.666666666666664], [1.731747624E12, 12.444444444444445]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747658E12, "title": "Latencies Over Time"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response latencies in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendLatenciesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average latency was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesLatenciesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotLatenciesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewLatenciesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Latencies Over Time
function refreshLatenciesOverTime(fixTimestamps) {
    var infos = latenciesOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyLatenciesOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotLatenciesOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesLatenciesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotLatenciesOverTime", "#overviewLatenciesOverTime");
        $('#footerLatenciesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var connectTimeOverTimeInfos = {
        data: {"result": {"minY": 0.05555555555555555, "minX": 1.731747599E12, "maxY": 1.166666666666667, "series": [{"data": [[1.73174763E12, 0.1714285714285715], [1.731747632E12, 0.05882352941176472], [1.731747628E12, 0.23333333333333342], [1.731747636E12, 0.08333333333333334], [1.731747634E12, 0.10000000000000002], [1.731747599E12, 1.166666666666667], [1.731747642E12, 0.05555555555555555], [1.731747638E12, 0.1470588235294118], [1.73174764E12, 0.1333333333333334], [1.731747603E12, 0.21621621621621626], [1.731747646E12, 0.1666666666666667], [1.731747605E12, 0.19354838709677424], [1.731747648E12, 0.1388888888888889], [1.731747601E12, 0.27272727272727265], [1.731747644E12, 0.17142857142857149], [1.731747609E12, 0.18918918918918923], [1.731747652E12, 0.2], [1.731747607E12, 0.23333333333333342], [1.73174765E12, 0.1470588235294118], [1.731747615E12, 0.1111111111111111], [1.731747658E12, 0.1666666666666667], [1.731747611E12, 0.20588235294117652], [1.731747654E12, 0.22222222222222227], [1.731747613E12, 0.19999999999999998], [1.731747656E12, 0.23529411764705888], [1.731747619E12, 0.13333333333333336], [1.731747621E12, 0.08333333333333334], [1.731747617E12, 0.21212121212121215], [1.731747625E12, 0.1333333333333334], [1.731747623E12, 0.17647058823529416], [1.731747631E12, 0.2], [1.731747627E12, 0.05555555555555555], [1.731747629E12, 0.22857142857142862], [1.731747635E12, 0.11764705882352944], [1.731747637E12, 0.16666666666666666], [1.731747633E12, 0.1388888888888889], [1.731747641E12, 0.11764705882352944], [1.7317476E12, 0.2702702702702703], [1.731747639E12, 0.16666666666666666], [1.731747604E12, 0.12121212121212124], [1.731747647E12, 0.14705882352941177], [1.731747643E12, 0.10000000000000002], [1.731747645E12, 0.1714285714285715], [1.731747602E12, 0.2], [1.731747651E12, 0.08333333333333334], [1.731747653E12, 0.11764705882352944], [1.73174761E12, 0.1333333333333334], [1.731747649E12, 0.10000000000000002], [1.731747606E12, 0.07692307692307693], [1.731747608E12, 0.15151515151515155], [1.731747657E12, 0.08333333333333334], [1.731747614E12, 0.20588235294117652], [1.731747616E12, 0.2666666666666667], [1.731747612E12, 0.08333333333333334], [1.731747655E12, 0.13333333333333336], [1.73174762E12, 0.11764705882352944], [1.731747618E12, 0.1891891891891892], [1.731747626E12, 0.20588235294117652], [1.731747622E12, 0.10000000000000002], [1.731747624E12, 0.16666666666666669]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747658E12, "title": "Connect Time Over Time"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getConnectTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average Connect Time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendConnectTimeOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average connect time was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesConnectTimeOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotConnectTimeOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewConnectTimeOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Connect Time Over Time
function refreshConnectTimeOverTime(fixTimestamps) {
    var infos = connectTimeOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyConnectTimeOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotConnectTimeOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesConnectTimeOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotConnectTimeOverTime", "#overviewConnectTimeOverTime");
        $('#footerConnectTimeOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var responseTimePercentilesOverTimeInfos = {
        data: {"result": {"minY": 12.0, "minX": 1.731747599E12, "maxY": 26.0, "series": [{"data": [[1.73174763E12, 15.0], [1.731747632E12, 16.0], [1.731747628E12, 16.0], [1.731747636E12, 16.0], [1.731747634E12, 16.0], [1.731747599E12, 26.0], [1.731747642E12, 16.0], [1.731747638E12, 16.0], [1.73174764E12, 19.0], [1.731747603E12, 17.0], [1.731747646E12, 15.0], [1.731747605E12, 17.0], [1.731747648E12, 16.0], [1.731747601E12, 17.0], [1.731747644E12, 15.0], [1.731747609E12, 16.0], [1.731747652E12, 15.0], [1.731747607E12, 19.0], [1.73174765E12, 16.0], [1.731747615E12, 19.0], [1.731747658E12, 17.0], [1.731747611E12, 16.0], [1.731747654E12, 16.0], [1.731747613E12, 16.0], [1.731747656E12, 16.0], [1.731747619E12, 16.0], [1.731747621E12, 15.0], [1.731747617E12, 16.0], [1.731747625E12, 16.0], [1.731747623E12, 16.0], [1.731747631E12, 16.0], [1.731747627E12, 16.0], [1.731747629E12, 15.0], [1.731747635E12, 16.0], [1.731747637E12, 15.0], [1.731747633E12, 15.0], [1.731747641E12, 20.0], [1.7317476E12, 18.0], [1.731747639E12, 20.0], [1.731747604E12, 16.0], [1.731747647E12, 16.0], [1.731747643E12, 15.0], [1.731747645E12, 16.0], [1.731747602E12, 16.0], [1.731747651E12, 16.0], [1.731747653E12, 16.0], [1.73174761E12, 15.0], [1.731747649E12, 16.0], [1.731747606E12, 16.0], [1.731747608E12, 16.0], [1.731747657E12, 16.0], [1.731747614E12, 16.0], [1.731747616E12, 16.0], [1.731747612E12, 16.0], [1.731747655E12, 16.0], [1.73174762E12, 17.0], [1.731747618E12, 16.0], [1.731747626E12, 17.0], [1.731747622E12, 16.0], [1.731747624E12, 16.0]], "isOverall": false, "label": "Max", "isController": false}, {"data": [[1.73174763E12, 15.0], [1.731747632E12, 15.0], [1.731747628E12, 15.400000000000002], [1.731747636E12, 14.300000000000004], [1.731747634E12, 15.100000000000001], [1.731747599E12, 20.799999999999997], [1.731747642E12, 14.300000000000004], [1.731747638E12, 15.0], [1.73174764E12, 19.0], [1.731747603E12, 16.0], [1.731747646E12, 15.0], [1.731747605E12, 16.0], [1.731747648E12, 14.0], [1.731747601E12, 16.0], [1.731747644E12, 15.0], [1.731747609E12, 15.0], [1.731747652E12, 14.400000000000002], [1.731747607E12, 15.400000000000002], [1.73174765E12, 14.7], [1.731747615E12, 16.7], [1.731747658E12, 15.3], [1.731747611E12, 15.0], [1.731747654E12, 14.100000000000001], [1.731747613E12, 15.5], [1.731747656E12, 16.0], [1.731747619E12, 16.0], [1.731747621E12, 15.0], [1.731747617E12, 15.8], [1.731747625E12, 15.2], [1.731747623E12, 15.0], [1.731747631E12, 15.0], [1.731747627E12, 14.300000000000004], [1.731747629E12, 15.0], [1.731747635E12, 14.7], [1.731747637E12, 15.0], [1.731747633E12, 14.900000000000002], [1.731747641E12, 18.0], [1.7317476E12, 16.0], [1.731747639E12, 19.0], [1.731747604E12, 14.8], [1.731747647E12, 15.0], [1.731747643E12, 14.3], [1.731747645E12, 15.0], [1.731747602E12, 15.100000000000001], [1.731747651E12, 15.0], [1.731747653E12, 14.7], [1.73174761E12, 15.0], [1.731747649E12, 15.100000000000001], [1.731747606E12, 15.0], [1.731747608E12, 15.0], [1.731747657E12, 14.300000000000004], [1.731747614E12, 16.0], [1.731747616E12, 15.0], [1.731747612E12, 14.300000000000004], [1.731747655E12, 14.399999999999999], [1.73174762E12, 16.7], [1.731747618E12, 15.600000000000001], [1.731747626E12, 16.0], [1.731747622E12, 14.800000000000004], [1.731747624E12, 15.0]], "isOverall": false, "label": "90th percentile", "isController": false}, {"data": [[1.73174763E12, 15.0], [1.731747632E12, 16.0], [1.731747628E12, 16.0], [1.731747636E12, 16.0], [1.731747634E12, 16.0], [1.731747599E12, 26.0], [1.731747642E12, 16.0], [1.731747638E12, 16.0], [1.73174764E12, 19.0], [1.731747603E12, 17.0], [1.731747646E12, 15.0], [1.731747605E12, 17.0], [1.731747648E12, 16.0], [1.731747601E12, 17.0], [1.731747644E12, 15.0], [1.731747609E12, 16.0], [1.731747652E12, 15.0], [1.731747607E12, 19.0], [1.73174765E12, 16.0], [1.731747615E12, 19.0], [1.731747658E12, 17.0], [1.731747611E12, 16.0], [1.731747654E12, 16.0], [1.731747613E12, 16.0], [1.731747656E12, 16.0], [1.731747619E12, 16.0], [1.731747621E12, 15.0], [1.731747617E12, 16.0], [1.731747625E12, 16.0], [1.731747623E12, 16.0], [1.731747631E12, 16.0], [1.731747627E12, 16.0], [1.731747629E12, 15.0], [1.731747635E12, 16.0], [1.731747637E12, 15.0], [1.731747633E12, 15.0], [1.731747641E12, 20.0], [1.7317476E12, 18.0], [1.731747639E12, 20.0], [1.731747604E12, 16.0], [1.731747647E12, 16.0], [1.731747643E12, 15.0], [1.731747645E12, 16.0], [1.731747602E12, 16.0], [1.731747651E12, 16.0], [1.731747653E12, 16.0], [1.73174761E12, 15.0], [1.731747649E12, 16.0], [1.731747606E12, 16.0], [1.731747608E12, 16.0], [1.731747657E12, 16.0], [1.731747614E12, 16.0], [1.731747616E12, 16.0], [1.731747612E12, 16.0], [1.731747655E12, 16.0], [1.73174762E12, 17.0], [1.731747618E12, 16.0], [1.731747626E12, 17.0], [1.731747622E12, 16.0], [1.731747624E12, 16.0]], "isOverall": false, "label": "99th percentile", "isController": false}, {"data": [[1.73174763E12, 15.0], [1.731747632E12, 16.0], [1.731747628E12, 16.0], [1.731747636E12, 15.149999999999999], [1.731747634E12, 16.0], [1.731747599E12, 25.199999999999996], [1.731747642E12, 15.149999999999999], [1.731747638E12, 15.349999999999998], [1.73174764E12, 19.0], [1.731747603E12, 16.4], [1.731747646E12, 15.0], [1.731747605E12, 16.5], [1.731747648E12, 15.45], [1.731747601E12, 16.5], [1.731747644E12, 15.0], [1.731747609E12, 15.5], [1.731747652E12, 15.0], [1.731747607E12, 18.099999999999998], [1.73174765E12, 16.0], [1.731747615E12, 19.0], [1.731747658E12, 16.65], [1.731747611E12, 16.0], [1.731747654E12, 15.549999999999997], [1.731747613E12, 16.0], [1.731747656E12, 16.0], [1.731747619E12, 16.0], [1.731747621E12, 15.0], [1.731747617E12, 16.0], [1.731747625E12, 16.0], [1.731747623E12, 16.0], [1.731747631E12, 15.649999999999999], [1.731747627E12, 15.149999999999999], [1.731747629E12, 15.0], [1.731747635E12, 15.349999999999998], [1.731747637E12, 15.0], [1.731747633E12, 15.0], [1.731747641E12, 20.0], [1.7317476E12, 17.4], [1.731747639E12, 19.549999999999997], [1.731747604E12, 16.0], [1.731747647E12, 16.0], [1.731747643E12, 15.0], [1.731747645E12, 15.45], [1.731747602E12, 16.0], [1.731747651E12, 16.0], [1.731747653E12, 15.349999999999998], [1.73174761E12, 15.0], [1.731747649E12, 16.0], [1.731747606E12, 16.0], [1.731747608E12, 16.0], [1.731747657E12, 15.149999999999999], [1.731747614E12, 16.0], [1.731747616E12, 15.649999999999999], [1.731747612E12, 16.0], [1.731747655E12, 16.0], [1.73174762E12, 17.0], [1.731747618E12, 16.0], [1.731747626E12, 16.5], [1.731747622E12, 16.0], [1.731747624E12, 15.549999999999997]], "isOverall": false, "label": "95th percentile", "isController": false}, {"data": [[1.73174763E12, 13.0], [1.731747632E12, 13.0], [1.731747628E12, 13.0], [1.731747636E12, 13.0], [1.731747634E12, 13.0], [1.731747599E12, 14.0], [1.731747642E12, 13.0], [1.731747638E12, 12.0], [1.73174764E12, 13.0], [1.731747603E12, 13.0], [1.731747646E12, 13.0], [1.731747605E12, 13.0], [1.731747648E12, 13.0], [1.731747601E12, 13.0], [1.731747644E12, 12.0], [1.731747609E12, 13.0], [1.731747652E12, 12.0], [1.731747607E12, 13.0], [1.73174765E12, 13.0], [1.731747615E12, 13.0], [1.731747658E12, 13.0], [1.731747611E12, 13.0], [1.731747654E12, 13.0], [1.731747613E12, 13.0], [1.731747656E12, 13.0], [1.731747619E12, 13.0], [1.731747621E12, 13.0], [1.731747617E12, 13.0], [1.731747625E12, 13.0], [1.731747623E12, 13.0], [1.731747631E12, 12.0], [1.731747627E12, 13.0], [1.731747629E12, 13.0], [1.731747635E12, 13.0], [1.731747637E12, 13.0], [1.731747633E12, 12.0], [1.731747641E12, 13.0], [1.7317476E12, 14.0], [1.731747639E12, 13.0], [1.731747604E12, 13.0], [1.731747647E12, 13.0], [1.731747643E12, 13.0], [1.731747645E12, 13.0], [1.731747602E12, 14.0], [1.731747651E12, 13.0], [1.731747653E12, 13.0], [1.73174761E12, 13.0], [1.731747649E12, 12.0], [1.731747606E12, 13.0], [1.731747608E12, 13.0], [1.731747657E12, 13.0], [1.731747614E12, 13.0], [1.731747616E12, 13.0], [1.731747612E12, 13.0], [1.731747655E12, 13.0], [1.73174762E12, 13.0], [1.731747618E12, 12.0], [1.731747626E12, 13.0], [1.731747622E12, 13.0], [1.731747624E12, 13.0]], "isOverall": false, "label": "Min", "isController": false}, {"data": [[1.73174763E12, 13.0], [1.731747632E12, 13.0], [1.731747628E12, 14.0], [1.731747636E12, 13.0], [1.731747634E12, 14.0], [1.731747599E12, 15.0], [1.731747642E12, 13.0], [1.731747638E12, 13.0], [1.73174764E12, 16.0], [1.731747603E12, 14.0], [1.731747646E12, 13.0], [1.731747605E12, 14.0], [1.731747648E12, 13.0], [1.731747601E12, 14.0], [1.731747644E12, 13.0], [1.731747609E12, 13.0], [1.731747652E12, 13.0], [1.731747607E12, 13.0], [1.73174765E12, 13.0], [1.731747615E12, 14.0], [1.731747658E12, 14.0], [1.731747611E12, 14.0], [1.731747654E12, 14.0], [1.731747613E12, 14.0], [1.731747656E12, 14.0], [1.731747619E12, 14.0], [1.731747621E12, 14.0], [1.731747617E12, 14.0], [1.731747625E12, 14.0], [1.731747623E12, 14.0], [1.731747631E12, 13.0], [1.731747627E12, 13.0], [1.731747629E12, 13.0], [1.731747635E12, 13.0], [1.731747637E12, 13.0], [1.731747633E12, 13.0], [1.731747641E12, 13.0], [1.7317476E12, 14.0], [1.731747639E12, 14.0], [1.731747604E12, 13.0], [1.731747647E12, 13.0], [1.731747643E12, 14.0], [1.731747645E12, 13.0], [1.731747602E12, 14.0], [1.731747651E12, 13.0], [1.731747653E12, 13.0], [1.73174761E12, 13.0], [1.731747649E12, 13.0], [1.731747606E12, 14.0], [1.731747608E12, 14.0], [1.731747657E12, 14.0], [1.731747614E12, 14.0], [1.731747616E12, 14.0], [1.731747612E12, 13.0], [1.731747655E12, 14.0], [1.73174762E12, 14.0], [1.731747618E12, 13.0], [1.731747626E12, 14.0], [1.731747622E12, 13.0], [1.731747624E12, 14.0]], "isOverall": false, "label": "Median", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747658E12, "title": "Response Time Percentiles Over Time (successful requests only)"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true,
                        fill: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Response Time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimePercentilesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Response time was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimePercentilesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimePercentilesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimePercentilesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Response Time Percentiles Over Time
function refreshResponseTimePercentilesOverTime(fixTimestamps) {
    var infos = responseTimePercentilesOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotResponseTimePercentilesOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesResponseTimePercentilesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimePercentilesOverTime", "#overviewResponseTimePercentilesOverTime");
        $('#footerResponseTimePercentilesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var responseTimeVsRequestInfos = {
    data: {"result": {"minY": 7.5, "minX": 30.0, "maxY": 14.0, "series": [{"data": [[33.0, 14.0], [34.0, 14.0], [35.0, 13.0], [37.0, 14.0], [36.0, 14.0], [39.0, 14.0], [30.0, 14.0], [31.0, 14.0]], "isOverall": false, "label": "Successes", "isController": false}, {"data": [[33.0, 8.0], [34.0, 8.0], [35.0, 8.0], [37.0, 8.0], [36.0, 8.0], [30.0, 8.0], [31.0, 7.5]], "isOverall": false, "label": "Failures", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 39.0, "title": "Response Time Vs Request"}},
    getOptions: function() {
        return {
            series: {
                lines: {
                    show: false
                },
                points: {
                    show: true
                }
            },
            xaxis: {
                axisLabel: "Global number of requests per second",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            yaxis: {
                axisLabel: "Median Response Time in ms",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            legend: {
                noColumns: 2,
                show: true,
                container: '#legendResponseTimeVsRequest'
            },
            selection: {
                mode: 'xy'
            },
            grid: {
                hoverable: true // IMPORTANT! this is needed for tooltip to work
            },
            tooltip: true,
            tooltipOpts: {
                content: "%s : Median response time at %x req/s was %y ms"
            },
            colors: ["#9ACD32", "#FF6347"]
        };
    },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesResponseTimeVsRequest"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotResponseTimeVsRequest"), dataset, options);
        // setup overview
        $.plot($("#overviewResponseTimeVsRequest"), dataset, prepareOverviewOptions(options));

    }
};

// Response Time vs Request
function refreshResponseTimeVsRequest() {
    var infos = responseTimeVsRequestInfos;
    prepareSeries(infos.data);
    if (isGraph($("#flotResponseTimeVsRequest"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimeVsRequest");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimeVsRequest", "#overviewResponseTimeVsRequest");
        $('#footerResponseRimeVsRequest .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var latenciesVsRequestInfos = {
    data: {"result": {"minY": 7.5, "minX": 30.0, "maxY": 14.0, "series": [{"data": [[33.0, 14.0], [34.0, 13.5], [35.0, 13.0], [37.0, 14.0], [36.0, 14.0], [39.0, 14.0], [30.0, 14.0], [31.0, 14.0]], "isOverall": false, "label": "Successes", "isController": false}, {"data": [[33.0, 8.0], [34.0, 8.0], [35.0, 8.0], [37.0, 8.0], [36.0, 8.0], [30.0, 8.0], [31.0, 7.5]], "isOverall": false, "label": "Failures", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 39.0, "title": "Latencies Vs Request"}},
    getOptions: function() {
        return{
            series: {
                lines: {
                    show: false
                },
                points: {
                    show: true
                }
            },
            xaxis: {
                axisLabel: "Global number of requests per second",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            yaxis: {
                axisLabel: "Median Latency in ms",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            legend: { noColumns: 2,show: true, container: '#legendLatencyVsRequest' },
            selection: {
                mode: 'xy'
            },
            grid: {
                hoverable: true // IMPORTANT! this is needed for tooltip to work
            },
            tooltip: true,
            tooltipOpts: {
                content: "%s : Median Latency time at %x req/s was %y ms"
            },
            colors: ["#9ACD32", "#FF6347"]
        };
    },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesLatencyVsRequest"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotLatenciesVsRequest"), dataset, options);
        // setup overview
        $.plot($("#overviewLatenciesVsRequest"), dataset, prepareOverviewOptions(options));
    }
};

// Latencies vs Request
function refreshLatenciesVsRequest() {
        var infos = latenciesVsRequestInfos;
        prepareSeries(infos.data);
        if(isGraph($("#flotLatenciesVsRequest"))){
            infos.createGraph();
        }else{
            var choiceContainer = $("#choicesLatencyVsRequest");
            createLegend(choiceContainer, infos);
            infos.createGraph();
            setGraphZoomable("#flotLatenciesVsRequest", "#overviewLatenciesVsRequest");
            $('#footerLatenciesVsRequest .legendColorBox > div').each(function(i){
                $(this).clone().prependTo(choiceContainer.find("li").eq(i));
            });
        }
};

var hitsPerSecondInfos = {
        data: {"result": {"minY": 30.0, "minX": 1.731747599E12, "maxY": 38.0, "series": [{"data": [[1.73174763E12, 34.0], [1.731747632E12, 35.0], [1.731747628E12, 30.0], [1.731747636E12, 35.0], [1.731747634E12, 30.0], [1.731747599E12, 30.0], [1.731747642E12, 35.0], [1.731747638E12, 35.0], [1.73174764E12, 30.0], [1.731747603E12, 38.0], [1.731747646E12, 30.0], [1.731747605E12, 32.0], [1.731747648E12, 35.0], [1.731747601E12, 32.0], [1.731747644E12, 36.0], [1.731747609E12, 36.0], [1.731747652E12, 30.0], [1.731747607E12, 30.0], [1.73174765E12, 35.0], [1.731747615E12, 35.0], [1.731747658E12, 30.0], [1.731747611E12, 35.0], [1.731747654E12, 35.0], [1.731747613E12, 30.0], [1.731747656E12, 35.0], [1.731747619E12, 30.0], [1.731747621E12, 35.0], [1.731747617E12, 34.0], [1.731747625E12, 30.0], [1.731747623E12, 35.0], [1.731747631E12, 30.0], [1.731747627E12, 35.0], [1.731747629E12, 36.0], [1.731747635E12, 35.0], [1.731747637E12, 30.0], [1.731747633E12, 35.0], [1.731747641E12, 35.0], [1.7317476E12, 38.0], [1.731747639E12, 35.0], [1.731747604E12, 32.0], [1.731747647E12, 35.0], [1.731747643E12, 30.0], [1.731747645E12, 34.0], [1.731747602E12, 30.0], [1.731747651E12, 35.0], [1.731747653E12, 35.0], [1.73174761E12, 30.0], [1.731747649E12, 30.0], [1.731747606E12, 38.0], [1.731747608E12, 34.0], [1.731747657E12, 35.0], [1.731747614E12, 35.0], [1.731747616E12, 30.0], [1.731747612E12, 35.0], [1.731747655E12, 30.0], [1.73174762E12, 35.0], [1.731747618E12, 36.0], [1.731747626E12, 35.0], [1.731747622E12, 30.0], [1.731747624E12, 35.0]], "isOverall": false, "label": "hitsPerSecond", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747658E12, "title": "Hits Per Second"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of hits / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendHitsPerSecond"
                },
                selection: {
                    mode : 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y.2 hits/sec"
                }
            };
        },
        createGraph: function createGraph() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesHitsPerSecond"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotHitsPerSecond"), dataset, options);
            // setup overview
            $.plot($("#overviewHitsPerSecond"), dataset, prepareOverviewOptions(options));
        }
};

// Hits per second
function refreshHitsPerSecond(fixTimestamps) {
    var infos = hitsPerSecondInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if (isGraph($("#flotHitsPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesHitsPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotHitsPerSecond", "#overviewHitsPerSecond");
        $('#footerHitsPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var codesPerSecondInfos = {
        data: {"result": {"minY": 2.0, "minX": 1.731747599E12, "maxY": 39.0, "series": [{"data": [[1.73174763E12, 31.0], [1.731747632E12, 32.0], [1.731747628E12, 25.0], [1.731747636E12, 36.0], [1.731747634E12, 28.0], [1.731747599E12, 27.0], [1.731747642E12, 36.0], [1.731747638E12, 32.0], [1.73174764E12, 27.0], [1.731747603E12, 31.0], [1.731747646E12, 26.0], [1.731747605E12, 29.0], [1.731747648E12, 30.0], [1.731747601E12, 29.0], [1.731747644E12, 28.0], [1.731747609E12, 29.0], [1.731747652E12, 25.0], [1.731747607E12, 25.0], [1.73174765E12, 32.0], [1.731747615E12, 32.0], [1.731747658E12, 26.0], [1.731747611E12, 29.0], [1.731747654E12, 28.0], [1.731747613E12, 24.0], [1.731747656E12, 29.0], [1.731747619E12, 28.0], [1.731747621E12, 36.0], [1.731747617E12, 31.0], [1.731747625E12, 27.0], [1.731747623E12, 32.0], [1.731747631E12, 26.0], [1.731747627E12, 36.0], [1.731747629E12, 28.0], [1.731747635E12, 32.0], [1.731747637E12, 25.0], [1.731747633E12, 30.0], [1.731747641E12, 29.0], [1.7317476E12, 31.0], [1.731747639E12, 28.0], [1.731747604E12, 31.0], [1.731747647E12, 32.0], [1.731747643E12, 26.0], [1.731747645E12, 30.0], [1.731747602E12, 28.0], [1.731747651E12, 36.0], [1.731747653E12, 32.0], [1.73174761E12, 27.0], [1.731747649E12, 28.0], [1.731747606E12, 39.0], [1.731747608E12, 31.0], [1.731747657E12, 36.0], [1.731747614E12, 28.0], [1.731747616E12, 26.0], [1.731747612E12, 36.0], [1.731747655E12, 27.0], [1.73174762E12, 32.0], [1.731747618E12, 31.0], [1.731747626E12, 29.0], [1.731747622E12, 25.0], [1.731747624E12, 28.0]], "isOverall": false, "label": "200", "isController": false}, {"data": [[1.73174763E12, 4.0], [1.731747632E12, 2.0], [1.731747628E12, 5.0], [1.731747634E12, 2.0], [1.731747599E12, 3.0], [1.731747638E12, 2.0], [1.73174764E12, 3.0], [1.731747603E12, 6.0], [1.731747646E12, 4.0], [1.731747605E12, 2.0], [1.731747648E12, 6.0], [1.731747601E12, 4.0], [1.731747644E12, 7.0], [1.731747609E12, 8.0], [1.731747652E12, 5.0], [1.731747607E12, 5.0], [1.73174765E12, 2.0], [1.731747615E12, 4.0], [1.731747658E12, 4.0], [1.731747611E12, 5.0], [1.731747654E12, 8.0], [1.731747613E12, 6.0], [1.731747656E12, 5.0], [1.731747619E12, 2.0], [1.731747617E12, 2.0], [1.731747625E12, 3.0], [1.731747623E12, 2.0], [1.731747631E12, 4.0], [1.731747629E12, 7.0], [1.731747635E12, 2.0], [1.731747637E12, 5.0], [1.731747633E12, 6.0], [1.731747641E12, 5.0], [1.7317476E12, 6.0], [1.731747639E12, 8.0], [1.731747604E12, 2.0], [1.731747647E12, 2.0], [1.731747643E12, 4.0], [1.731747645E12, 5.0], [1.731747602E12, 2.0], [1.731747653E12, 2.0], [1.73174761E12, 3.0], [1.731747649E12, 2.0], [1.731747608E12, 2.0], [1.731747614E12, 6.0], [1.731747616E12, 4.0], [1.731747655E12, 3.0], [1.73174762E12, 2.0], [1.731747618E12, 6.0], [1.731747626E12, 5.0], [1.731747622E12, 5.0], [1.731747624E12, 8.0]], "isOverall": false, "label": "500", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747658E12, "title": "Codes Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of responses / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendCodesPerSecond"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "Number of Response Codes %s at %x was %y.2 responses / sec"
                }
            };
        },
    createGraph: function() {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesCodesPerSecond"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotCodesPerSecond"), dataset, options);
        // setup overview
        $.plot($("#overviewCodesPerSecond"), dataset, prepareOverviewOptions(options));
    }
};

// Codes per second
function refreshCodesPerSecond(fixTimestamps) {
    var infos = codesPerSecondInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotCodesPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesCodesPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotCodesPerSecond", "#overviewCodesPerSecond");
        $('#footerCodesPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var transactionsPerSecondInfos = {
        data: {"result": {"minY": 2.0, "minX": 1.731747599E12, "maxY": 39.0, "series": [{"data": [[1.73174763E12, 4.0], [1.731747632E12, 2.0], [1.731747628E12, 5.0], [1.731747634E12, 2.0], [1.731747599E12, 3.0], [1.731747638E12, 2.0], [1.73174764E12, 3.0], [1.731747603E12, 6.0], [1.731747646E12, 4.0], [1.731747605E12, 2.0], [1.731747648E12, 6.0], [1.731747601E12, 4.0], [1.731747644E12, 7.0], [1.731747609E12, 8.0], [1.731747652E12, 5.0], [1.731747607E12, 5.0], [1.73174765E12, 2.0], [1.731747615E12, 4.0], [1.731747658E12, 4.0], [1.731747611E12, 5.0], [1.731747654E12, 8.0], [1.731747613E12, 6.0], [1.731747656E12, 5.0], [1.731747619E12, 2.0], [1.731747617E12, 2.0], [1.731747625E12, 3.0], [1.731747623E12, 2.0], [1.731747631E12, 4.0], [1.731747629E12, 7.0], [1.731747635E12, 2.0], [1.731747637E12, 5.0], [1.731747633E12, 6.0], [1.731747641E12, 5.0], [1.7317476E12, 6.0], [1.731747639E12, 8.0], [1.731747604E12, 2.0], [1.731747647E12, 2.0], [1.731747643E12, 4.0], [1.731747645E12, 5.0], [1.731747602E12, 2.0], [1.731747653E12, 2.0], [1.73174761E12, 3.0], [1.731747649E12, 2.0], [1.731747608E12, 2.0], [1.731747614E12, 6.0], [1.731747616E12, 4.0], [1.731747655E12, 3.0], [1.73174762E12, 2.0], [1.731747618E12, 6.0], [1.731747626E12, 5.0], [1.731747622E12, 5.0], [1.731747624E12, 8.0]], "isOverall": false, "label": "Products-failure", "isController": false}, {"data": [[1.73174763E12, 31.0], [1.731747632E12, 32.0], [1.731747628E12, 25.0], [1.731747636E12, 36.0], [1.731747634E12, 28.0], [1.731747599E12, 27.0], [1.731747642E12, 36.0], [1.731747638E12, 32.0], [1.73174764E12, 27.0], [1.731747603E12, 31.0], [1.731747646E12, 26.0], [1.731747605E12, 29.0], [1.731747648E12, 30.0], [1.731747601E12, 29.0], [1.731747644E12, 28.0], [1.731747609E12, 29.0], [1.731747652E12, 25.0], [1.731747607E12, 25.0], [1.73174765E12, 32.0], [1.731747615E12, 32.0], [1.731747658E12, 26.0], [1.731747611E12, 29.0], [1.731747654E12, 28.0], [1.731747613E12, 24.0], [1.731747656E12, 29.0], [1.731747619E12, 28.0], [1.731747621E12, 36.0], [1.731747617E12, 31.0], [1.731747625E12, 27.0], [1.731747623E12, 32.0], [1.731747631E12, 26.0], [1.731747627E12, 36.0], [1.731747629E12, 28.0], [1.731747635E12, 32.0], [1.731747637E12, 25.0], [1.731747633E12, 30.0], [1.731747641E12, 29.0], [1.7317476E12, 31.0], [1.731747639E12, 28.0], [1.731747604E12, 31.0], [1.731747647E12, 32.0], [1.731747643E12, 26.0], [1.731747645E12, 30.0], [1.731747602E12, 28.0], [1.731747651E12, 36.0], [1.731747653E12, 32.0], [1.73174761E12, 27.0], [1.731747649E12, 28.0], [1.731747606E12, 39.0], [1.731747608E12, 31.0], [1.731747657E12, 36.0], [1.731747614E12, 28.0], [1.731747616E12, 26.0], [1.731747612E12, 36.0], [1.731747655E12, 27.0], [1.73174762E12, 32.0], [1.731747618E12, 31.0], [1.731747626E12, 29.0], [1.731747622E12, 25.0], [1.731747624E12, 28.0]], "isOverall": false, "label": "Products-success", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747658E12, "title": "Transactions Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of transactions / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendTransactionsPerSecond"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y transactions / sec"
                }
            };
        },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesTransactionsPerSecond"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotTransactionsPerSecond"), dataset, options);
        // setup overview
        $.plot($("#overviewTransactionsPerSecond"), dataset, prepareOverviewOptions(options));
    }
};

// Transactions per second
function refreshTransactionsPerSecond(fixTimestamps) {
    var infos = transactionsPerSecondInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyTransactionsPerSecond");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotTransactionsPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTransactionsPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTransactionsPerSecond", "#overviewTransactionsPerSecond");
        $('#footerTransactionsPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var totalTPSInfos = {
        data: {"result": {"minY": 2.0, "minX": 1.731747599E12, "maxY": 39.0, "series": [{"data": [[1.73174763E12, 31.0], [1.731747632E12, 32.0], [1.731747628E12, 25.0], [1.731747636E12, 36.0], [1.731747634E12, 28.0], [1.731747599E12, 27.0], [1.731747642E12, 36.0], [1.731747638E12, 32.0], [1.73174764E12, 27.0], [1.731747603E12, 31.0], [1.731747646E12, 26.0], [1.731747605E12, 29.0], [1.731747648E12, 30.0], [1.731747601E12, 29.0], [1.731747644E12, 28.0], [1.731747609E12, 29.0], [1.731747652E12, 25.0], [1.731747607E12, 25.0], [1.73174765E12, 32.0], [1.731747615E12, 32.0], [1.731747658E12, 26.0], [1.731747611E12, 29.0], [1.731747654E12, 28.0], [1.731747613E12, 24.0], [1.731747656E12, 29.0], [1.731747619E12, 28.0], [1.731747621E12, 36.0], [1.731747617E12, 31.0], [1.731747625E12, 27.0], [1.731747623E12, 32.0], [1.731747631E12, 26.0], [1.731747627E12, 36.0], [1.731747629E12, 28.0], [1.731747635E12, 32.0], [1.731747637E12, 25.0], [1.731747633E12, 30.0], [1.731747641E12, 29.0], [1.7317476E12, 31.0], [1.731747639E12, 28.0], [1.731747604E12, 31.0], [1.731747647E12, 32.0], [1.731747643E12, 26.0], [1.731747645E12, 30.0], [1.731747602E12, 28.0], [1.731747651E12, 36.0], [1.731747653E12, 32.0], [1.73174761E12, 27.0], [1.731747649E12, 28.0], [1.731747606E12, 39.0], [1.731747608E12, 31.0], [1.731747657E12, 36.0], [1.731747614E12, 28.0], [1.731747616E12, 26.0], [1.731747612E12, 36.0], [1.731747655E12, 27.0], [1.73174762E12, 32.0], [1.731747618E12, 31.0], [1.731747626E12, 29.0], [1.731747622E12, 25.0], [1.731747624E12, 28.0]], "isOverall": false, "label": "Transaction-success", "isController": false}, {"data": [[1.73174763E12, 4.0], [1.731747632E12, 2.0], [1.731747628E12, 5.0], [1.731747634E12, 2.0], [1.731747599E12, 3.0], [1.731747638E12, 2.0], [1.73174764E12, 3.0], [1.731747603E12, 6.0], [1.731747646E12, 4.0], [1.731747605E12, 2.0], [1.731747648E12, 6.0], [1.731747601E12, 4.0], [1.731747644E12, 7.0], [1.731747609E12, 8.0], [1.731747652E12, 5.0], [1.731747607E12, 5.0], [1.73174765E12, 2.0], [1.731747615E12, 4.0], [1.731747658E12, 4.0], [1.731747611E12, 5.0], [1.731747654E12, 8.0], [1.731747613E12, 6.0], [1.731747656E12, 5.0], [1.731747619E12, 2.0], [1.731747617E12, 2.0], [1.731747625E12, 3.0], [1.731747623E12, 2.0], [1.731747631E12, 4.0], [1.731747629E12, 7.0], [1.731747635E12, 2.0], [1.731747637E12, 5.0], [1.731747633E12, 6.0], [1.731747641E12, 5.0], [1.7317476E12, 6.0], [1.731747639E12, 8.0], [1.731747604E12, 2.0], [1.731747647E12, 2.0], [1.731747643E12, 4.0], [1.731747645E12, 5.0], [1.731747602E12, 2.0], [1.731747653E12, 2.0], [1.73174761E12, 3.0], [1.731747649E12, 2.0], [1.731747608E12, 2.0], [1.731747614E12, 6.0], [1.731747616E12, 4.0], [1.731747655E12, 3.0], [1.73174762E12, 2.0], [1.731747618E12, 6.0], [1.731747626E12, 5.0], [1.731747622E12, 5.0], [1.731747624E12, 8.0]], "isOverall": false, "label": "Transaction-failure", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747658E12, "title": "Total Transactions Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of transactions / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendTotalTPS"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y transactions / sec"
                },
                colors: ["#9ACD32", "#FF6347"]
            };
        },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesTotalTPS"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotTotalTPS"), dataset, options);
        // setup overview
        $.plot($("#overviewTotalTPS"), dataset, prepareOverviewOptions(options));
    }
};

// Total Transactions per second
function refreshTotalTPS(fixTimestamps) {
    var infos = totalTPSInfos;
    // We want to ignore seriesFilter
    prepareSeries(infos.data, false, true);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotTotalTPS"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTotalTPS");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTotalTPS", "#overviewTotalTPS");
        $('#footerTotalTPS .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

// Collapse the graph matching the specified DOM element depending the collapsed
// status
function collapse(elem, collapsed){
    if(collapsed){
        $(elem).parent().find(".fa-chevron-up").removeClass("fa-chevron-up").addClass("fa-chevron-down");
    } else {
        $(elem).parent().find(".fa-chevron-down").removeClass("fa-chevron-down").addClass("fa-chevron-up");
        if (elem.id == "bodyBytesThroughputOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshBytesThroughputOverTime(true);
            }
            document.location.href="#bytesThroughputOverTime";
        } else if (elem.id == "bodyLatenciesOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshLatenciesOverTime(true);
            }
            document.location.href="#latenciesOverTime";
        } else if (elem.id == "bodyCustomGraph") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshCustomGraph(true);
            }
            document.location.href="#responseCustomGraph";
        } else if (elem.id == "bodyConnectTimeOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshConnectTimeOverTime(true);
            }
            document.location.href="#connectTimeOverTime";
        } else if (elem.id == "bodyResponseTimePercentilesOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimePercentilesOverTime(true);
            }
            document.location.href="#responseTimePercentilesOverTime";
        } else if (elem.id == "bodyResponseTimeDistribution") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimeDistribution();
            }
            document.location.href="#responseTimeDistribution" ;
        } else if (elem.id == "bodySyntheticResponseTimeDistribution") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshSyntheticResponseTimeDistribution();
            }
            document.location.href="#syntheticResponseTimeDistribution" ;
        } else if (elem.id == "bodyActiveThreadsOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshActiveThreadsOverTime(true);
            }
            document.location.href="#activeThreadsOverTime";
        } else if (elem.id == "bodyTimeVsThreads") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTimeVsThreads();
            }
            document.location.href="#timeVsThreads" ;
        } else if (elem.id == "bodyCodesPerSecond") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshCodesPerSecond(true);
            }
            document.location.href="#codesPerSecond";
        } else if (elem.id == "bodyTransactionsPerSecond") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTransactionsPerSecond(true);
            }
            document.location.href="#transactionsPerSecond";
        } else if (elem.id == "bodyTotalTPS") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTotalTPS(true);
            }
            document.location.href="#totalTPS";
        } else if (elem.id == "bodyResponseTimeVsRequest") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimeVsRequest();
            }
            document.location.href="#responseTimeVsRequest";
        } else if (elem.id == "bodyLatenciesVsRequest") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshLatenciesVsRequest();
            }
            document.location.href="#latencyVsRequest";
        }
    }
}

/*
 * Activates or deactivates all series of the specified graph (represented by id parameter)
 * depending on checked argument.
 */
function toggleAll(id, checked){
    var placeholder = document.getElementById(id);

    var cases = $(placeholder).find(':checkbox');
    cases.prop('checked', checked);
    $(cases).parent().children().children().toggleClass("legend-disabled", !checked);

    var choiceContainer;
    if ( id == "choicesBytesThroughputOverTime"){
        choiceContainer = $("#choicesBytesThroughputOverTime");
        refreshBytesThroughputOverTime(false);
    } else if(id == "choicesResponseTimesOverTime"){
        choiceContainer = $("#choicesResponseTimesOverTime");
        refreshResponseTimeOverTime(false);
    }else if(id == "choicesResponseCustomGraph"){
        choiceContainer = $("#choicesResponseCustomGraph");
        refreshCustomGraph(false);
    } else if ( id == "choicesLatenciesOverTime"){
        choiceContainer = $("#choicesLatenciesOverTime");
        refreshLatenciesOverTime(false);
    } else if ( id == "choicesConnectTimeOverTime"){
        choiceContainer = $("#choicesConnectTimeOverTime");
        refreshConnectTimeOverTime(false);
    } else if ( id == "choicesResponseTimePercentilesOverTime"){
        choiceContainer = $("#choicesResponseTimePercentilesOverTime");
        refreshResponseTimePercentilesOverTime(false);
    } else if ( id == "choicesResponseTimePercentiles"){
        choiceContainer = $("#choicesResponseTimePercentiles");
        refreshResponseTimePercentiles();
    } else if(id == "choicesActiveThreadsOverTime"){
        choiceContainer = $("#choicesActiveThreadsOverTime");
        refreshActiveThreadsOverTime(false);
    } else if ( id == "choicesTimeVsThreads"){
        choiceContainer = $("#choicesTimeVsThreads");
        refreshTimeVsThreads();
    } else if ( id == "choicesSyntheticResponseTimeDistribution"){
        choiceContainer = $("#choicesSyntheticResponseTimeDistribution");
        refreshSyntheticResponseTimeDistribution();
    } else if ( id == "choicesResponseTimeDistribution"){
        choiceContainer = $("#choicesResponseTimeDistribution");
        refreshResponseTimeDistribution();
    } else if ( id == "choicesHitsPerSecond"){
        choiceContainer = $("#choicesHitsPerSecond");
        refreshHitsPerSecond(false);
    } else if(id == "choicesCodesPerSecond"){
        choiceContainer = $("#choicesCodesPerSecond");
        refreshCodesPerSecond(false);
    } else if ( id == "choicesTransactionsPerSecond"){
        choiceContainer = $("#choicesTransactionsPerSecond");
        refreshTransactionsPerSecond(false);
    } else if ( id == "choicesTotalTPS"){
        choiceContainer = $("#choicesTotalTPS");
        refreshTotalTPS(false);
    } else if ( id == "choicesResponseTimeVsRequest"){
        choiceContainer = $("#choicesResponseTimeVsRequest");
        refreshResponseTimeVsRequest();
    } else if ( id == "choicesLatencyVsRequest"){
        choiceContainer = $("#choicesLatencyVsRequest");
        refreshLatenciesVsRequest();
    }
    var color = checked ? "black" : "#818181";
    if(choiceContainer != null) {
        choiceContainer.find("label").each(function(){
            this.style.color = color;
        });
    }
}

