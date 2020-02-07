# frozen_string_literal: true

# https://stackoverflow.com/questions/20234504/rails-devise-i18n-flash-messages-with-twitter-bootstrap
module DeviseHelper
  def devise_error_messages!
    return '' if resource.errors.empty?

    messages = resource.errors.full_messages.map { |msg| content_tag(:li, msg) }.join
    html = <<-HTML
    <div class="alert alert-<%= key %> alert-dismissible fade show" role="alert">
      #{messages}
      <button type="button" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
      </button>
    </div>
    HTML

    html.html_safe
  end
end
