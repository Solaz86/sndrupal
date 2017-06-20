(function ($) {
  Drupal.behaviors.carlosForm = {
    attach: function (context, settings) {
      // $('.alert-block').delay(500).fadeOut(1000)

      $('.edit-alt').click(function(e) {   // en objeto jquery ponermos una clase
        e.preventDefault()
        var $this = $(this)
        var id = $this.attr('data-id') // se asigna a var id el atributo data-id de $this
        $.ajax({
          url: '/carlos/edit/' + id,
          method: 'GET',
          success: function (data) {
            $('#edit-updatealt--2').hide()
            $('#edit-create--2').hide()
            $('.maintable').hide()
            $('#ide').val(id)
            $('#edit-name--2').val(data.name)
            $('#edit-lastname--2').val(data.lastname)
            $('#edit-tel--2').val(data.tel)
            $('#edit-age--2').val(data.age)
            $('#edit-opsex--2').val(data.opsex)

            if (!$('#back-create').length > 0) {
              $('#page-title').after("<div><a href='/carlos/pagina-custom'>"+settings.carlos_form.back+"</a></div>")
            }

          }
        });
      });

      $('#edit-updatealt--2').click(function(e) {
        e.preventDefault()
        const data = {
          userid: $('#ide').val(),
          name: $('#edit-name--2').val(),
          lastname: $('#edit-lastname--2').val(),
          tel: $('#edit-tel--2').val(),
          age: $('#edit-age--2').val(),
          opsex: $('#edit-opsex--2').val()
        }
        $.ajax({
          type: "POST",
          url: '/carlos/newedit',
          data: data,
          success: function(response) {
            console.log(response)
            if (response.code == 401) {
              $('.maintable').show()

              // Regenerar tabla
              var row = $('#row-user-' + response.user.id)
              console.log(row)
              row.each(function() {
                const lasttd = $(this).find(':last-child')
                row.empty().html(
                  '<td>'+response.user.id+'</td>'+
                  '<td>'+response.user.name+'</td>'+
                  '<td>'+response.user.lastname+'</td>'+
                  '<td>'+response.user.telefono+'</td>'+
                  '<td>'+response.user.age+'</td>'+
                  '<td>'+response.user.opsex+'</td>'+
                  lasttd.html()
                )
              });
            }
          }
        });
      });

      $('.delete-user').click(function(e) {
        e.preventDefault()
        var nameRow = $(this).parent().parent().attr('id').split('-')
        var idUser = nameRow[nameRow.length - 1]

        $.ajax({
          type: "POST",
          url: '/carlos/pagina/delete',
          data: {
            id: idUser
          },
          success: handlerDeleteUser
        })
      });

      function handlerDeleteUser (response) {
        if (response.code == 200) {
          $('#row-user-' + response.id).remove()
        }
      }


    }
  };
}(jQuery));