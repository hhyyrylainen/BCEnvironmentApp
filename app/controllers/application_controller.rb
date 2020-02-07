# frozen_string_literal: true

class ApplicationController < ActionController::Base
  def require_admin
    unless current_user&.admin?
      redirect_to root_path, alert: 'You have no permission to view this page'
    end
  end
end
