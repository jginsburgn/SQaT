require 'watir'

browser = Watir::Browser.new :chrome
url = "http://blazedemo.com/"
browser.goto(url);
from = browser.select name: 'fromPort'
from.options.each do |opt|
	#puts opt.value
end
from.select_value(from.options[1].value)
to = browser.select name: 'toPort'
to.select_value(to.options[2].value)
find_flights = browser.input value: 'Find Flights'
find_flights.click
browser.inputs(:type => "submit").last.click
browser.inputs(:type => "text").each do |input|
	input.send_keys("Lorem Ipsum")
end
browser.checkbox(:id => "rememberMe").set
browser.input(:value => "Purchase Flight").click
sleep 10
