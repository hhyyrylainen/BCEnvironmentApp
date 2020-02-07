# frozen_string_literal: true

# Base app controller with common filters
class ApplicationController < ActionController::Base
  private

  def require_admin
    return if current_user&.admin?

    redirect_to root_path, alert: 'You have no permission to view this page'
  end
end
