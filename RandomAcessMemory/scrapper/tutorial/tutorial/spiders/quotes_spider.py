import scrapy

'''
                To run the Spider
 I - go to the top level dir. of the project
 II - Execute in the terminal " $ scrapy crawl <spider_name> "
'''
# Define our spider class, which uses heritage from scrapy.Spider


class QuotesSpyder(scrapy.Spider):
    # Identify the spider. Must be unique within the program
    name = "quotes"
    # The start urls is an attribute that have the default behavior
    start_urls = [
        "https://uspdigital.usp.br/rucard/Jsp/cardapioSAS.jsp?codrtn=8"
    ]

    '''
    -->Yield an iterator request , somewhat like a generator function<--

    For each url in the list, the lib will make the request, return the
    response in the "response" object, and execute the callback function
    related (which in this case is the parse method)

    #Here is the custom interpretation of the method
    def start_requests(self):
        urls = [
                "http://quotes.toscrape.com/tag/life/",
                "http://quotes.toscrape.com/tag/love/"
                ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)
    '''

    '''
        Called for every request. It receives a response parameter ,
        which has useful methods to ultimately parse the content read from the
        website. It then saves an html into a file with the name define in the
        parse override method.
    '''

    def parse(self, response):
        page = response.url.split("/")[-2]
        filename = 'quotes-%s.html' % page
        with open(filename, 'wb') as f:
            f.write(response.body)
        self.log('Saved file %s' % filename)
