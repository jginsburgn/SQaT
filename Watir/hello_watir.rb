require 'watir'
browser = Watir::Browser.new :firefox

browser.goto 'http://nitrowriters.com/form/form.html'

#escribir sobre un cuadro de texto
browser.text_field(:id => "my_text_field").set("hola")

#escribir sobre un text area
browser.textarea(:id => "a_text_area").set "hppppppla"

#otra forma de escribir sobre un textArea
browser.div()

#permite obtener un radio por su id y asignarle un valor
browser.radio(:id => "familiar_rails_3").set

#permite obtener un conjunto de checkboxes y seleccionarlos todos ( /partially matches/ )
checks = browser.checkboxes(:name => /element_14/)
checks.each do |check|
    check.set
end

#contar el número de elementos que tiene un <select>
puts browser.select_list(:id => "usage").options.count

#selecciona la tercera opción de un <select>
opciones = browser.select_list(:id => "usage").options
cont = 0
opciones.each do |op|
    if (cont == 3)
        op.select
    end
    cont += 1
end

#otra forma de acceder a un <select>
#browser.select_list(:id => usage).find do |lista|
#    lista.option

#seleccionar un archivo y subirlo a una página (absolute path)
browser.file_field(:id => 'give_me_a_file').set("/home/ariellucien/hola.txt")


#dar click a un botón de submit
browser.button(:name => "submit").click



